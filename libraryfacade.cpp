#include "libraryfacade.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "readerfactory.h"

LibraryFacade::LibraryFacade()
{
    initDatabase();
}

LibraryFacade::~LibraryFacade()
{
    if (m_db.isOpen())
        m_db.close();
}

bool LibraryFacade::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("library.db");
    if (!m_db.open()) {
        qDebug() << "Cannot open database:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS books ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "title TEXT NOT NULL, "
               "author TEXT NOT NULL, "
               "year INTEGER, "
               "publisherId INTEGER, "
               "available INTEGER DEFAULT 1)");

    query.exec("CREATE TABLE IF NOT EXISTS readers ("
               "id INTEGER PRIMARY KEY, "
               "fullName TEXT NOT NULL, "
               "address TEXT, "
               "phone TEXT, "
               "type TEXT DEFAULT 'Новый')");

    query.exec("CREATE TABLE IF NOT EXISTS publishers ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "address TEXT, "
               "phone TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS loans ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "readerId INTEGER, "
               "bookId INTEGER, "
               "issueDate TEXT, "
               "returnDate TEXT)");

    return true;
}

bool LibraryFacade::addBook(const Book& book)
{
    QSqlQuery query;
    query.prepare("INSERT INTO books (title, author, year, publisherId, available) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(book.getTitle());
    query.addBindValue(book.getAuthor());
    query.addBindValue(book.getYear());
    query.addBindValue(book.getPublisherId());
    query.addBindValue(book.isAvailable() ? 1 : 0);
    return query.exec();
}

bool LibraryFacade::updateBook(const Book& book)
{
    QSqlQuery query;
    query.prepare("UPDATE books SET title=?, author=?, year=?, publisherId=?, available=? "
                  "WHERE id=?");
    query.addBindValue(book.getTitle());
    query.addBindValue(book.getAuthor());
    query.addBindValue(book.getYear());
    query.addBindValue(book.getPublisherId());
    query.addBindValue(book.isAvailable() ? 1 : 0);
    query.addBindValue(book.getId());
    return query.exec();
}

bool LibraryFacade::deleteBook(int bookId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM books WHERE id=?");
    query.addBindValue(bookId);
    return query.exec();
}

QSqlQueryModel* LibraryFacade::getAllBooksModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, title, author, year, "
                    "(SELECT name FROM publishers WHERE id=books.publisherId) as publisher, "
                    "CASE WHEN available=1 THEN 'В наличии' ELSE 'Выдана' END as status "
                    "FROM books");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Автор");
    model->setHeaderData(3, Qt::Horizontal, "Год");
    model->setHeaderData(4, Qt::Horizontal, "Издательство");
    model->setHeaderData(5, Qt::Horizontal, "Статус");
    return model;
}

QList<Book> LibraryFacade::getAvailableBooks()
{
    QList<Book> books;
    QSqlQuery query("SELECT id, title, author, year, publisherId, available "
                    "FROM books WHERE available=1");
    while (query.next()) {
        books.append(Book(query.value(0).toInt(),
                          query.value(1).toString(),
                          query.value(2).toString(),
                          query.value(3).toInt(),
                          query.value(4).toInt(),
                          query.value(5).toBool()));
    }
    return books;
}

bool LibraryFacade::addReader(Reader* reader)
{
    QSqlQuery query;
    query.prepare("INSERT INTO readers (id, fullName, address, phone, type) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(reader->getId());
    query.addBindValue(reader->getFullName());
    query.addBindValue(reader->getAddress());
    query.addBindValue(reader->getPhone());
    query.addBindValue(reader->getTypeName());
    bool ok = query.exec();
    delete reader;
    return ok;
}

bool LibraryFacade::updateReader(const Reader& reader)
{
    QSqlQuery query;
    query.prepare("UPDATE readers SET fullName=?, address=?, phone=?, type=? WHERE id=?");
    query.addBindValue(reader.getFullName());
    query.addBindValue(reader.getAddress());
    query.addBindValue(reader.getPhone());
    query.addBindValue(reader.getTypeName());
    query.addBindValue(reader.getId());
    return query.exec();
}

bool LibraryFacade::deleteReader(int readerId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM readers WHERE id=?");
    query.addBindValue(readerId);
    return query.exec();
}

QSqlQueryModel* LibraryFacade::getAllReadersModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, fullName, address, phone, type FROM readers");
    model->setHeaderData(0, Qt::Horizontal, "№ билета");
    model->setHeaderData(1, Qt::Horizontal, "ФИО");
    model->setHeaderData(2, Qt::Horizontal, "Адрес");
    model->setHeaderData(3, Qt::Horizontal, "Телефон");
    model->setHeaderData(4, Qt::Horizontal, "Категория");
    return model;
}

QList<Reader*> LibraryFacade::getAllReaders()
{
    QList<Reader*> readers;
    QSqlQuery query("SELECT id, fullName, address, phone, type FROM readers");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString addr = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString typeStr = query.value(4).toString();
        ReaderType type;
        if (typeStr == "Новый") type = ReaderType::New;
        else if (typeStr == "Постоянный") type = ReaderType::Regular;
        else type = ReaderType::Premium;
        readers.append(ReaderFactory::createReader(type, id, name, addr, phone));
    }
    return readers;
}

Reader* LibraryFacade::getReaderById(int readerId) const
{
    QSqlQuery query;
    query.prepare("SELECT id, fullName, address, phone, type FROM readers WHERE id = ?");
    query.addBindValue(readerId);
    if (query.exec() && query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString addr = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString typeStr = query.value(4).toString();
        ReaderType type;
        if (typeStr == "Новый") type = ReaderType::New;
        else if (typeStr == "Постоянный") type = ReaderType::Regular;
        else type = ReaderType::Premium;
        return ReaderFactory::createReader(type, id, name, addr, phone);
    }
    return nullptr;
}

bool LibraryFacade::addPublisher(const Publisher& publisher)
{
    QSqlQuery query;
    query.prepare("INSERT INTO publishers (name, address, phone) VALUES (?, ?, ?)");
    query.addBindValue(publisher.getName());
    query.addBindValue(publisher.getAddress());
    query.addBindValue(publisher.getPhone());
    return query.exec();
}

bool LibraryFacade::updatePublisher(const Publisher& publisher)
{
    QSqlQuery query;
    query.prepare("UPDATE publishers SET name=?, address=?, phone=? WHERE id=?");
    query.addBindValue(publisher.getName());
    query.addBindValue(publisher.getAddress());
    query.addBindValue(publisher.getPhone());
    query.addBindValue(publisher.getId());
    return query.exec();
}

bool LibraryFacade::deletePublisher(int publisherId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM publishers WHERE id=?");
    query.addBindValue(publisherId);
    return query.exec();
}

QSqlQueryModel* LibraryFacade::getAllPublishersModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, address, phone FROM publishers");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Адрес");
    model->setHeaderData(3, Qt::Horizontal, "Телефон");
    return model;
}

bool LibraryFacade::issueBook(int readerId, int bookId, const QDate& issueDate)
{
    QSqlQuery check;
    check.prepare("SELECT available FROM books WHERE id = ?");
    check.addBindValue(bookId);
    if (!check.exec() || !check.next() || check.value(0).toInt() == 0)
        return false;

    QSqlQuery insert;
    insert.prepare("INSERT INTO loans (readerId, bookId, issueDate, returnDate) "
                   "VALUES (?, ?, ?, NULL)");
    insert.addBindValue(readerId);
    insert.addBindValue(bookId);
    insert.addBindValue(issueDate.toString(Qt::ISODate));
    if (!insert.exec())
        return false;

    QSqlQuery update;
    update.prepare("UPDATE books SET available = 0 WHERE id = ?");
    update.addBindValue(bookId);
    return update.exec();
}

bool LibraryFacade::returnBook(int loanId, const QDate& returnDate)
{
    QSqlQuery getBook;
    getBook.prepare("SELECT bookId FROM loans WHERE id = ?");
    getBook.addBindValue(loanId);
    if (!getBook.exec() || !getBook.next())
        return false;
    int bookId = getBook.value(0).toInt();

    QSqlQuery updateLoan;
    updateLoan.prepare("UPDATE loans SET returnDate = ? WHERE id = ?");
    updateLoan.addBindValue(returnDate.toString(Qt::ISODate));
    updateLoan.addBindValue(loanId);
    if (!updateLoan.exec())
        return false;

    QSqlQuery updateBook;
    updateBook.prepare("UPDATE books SET available = 1 WHERE id = ?");
    updateBook.addBindValue(bookId);
    return updateBook.exec();
}

QSqlQueryModel* LibraryFacade::getAllLoansModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT l.id, "
                    "(SELECT fullName FROM readers WHERE id=l.readerId) as reader, "
                    "(SELECT title FROM books WHERE id=l.bookId) as book, "
                    "l.issueDate, "
                    "CASE WHEN l.returnDate IS NULL THEN 'Не возвращена' ELSE l.returnDate END as returnDate "
                    "FROM loans l");
    model->setHeaderData(0, Qt::Horizontal, "№");
    model->setHeaderData(1, Qt::Horizontal, "Читатель");
    model->setHeaderData(2, Qt::Horizontal, "Книга");
    model->setHeaderData(3, Qt::Horizontal, "Дата выдачи");
    model->setHeaderData(4, Qt::Horizontal, "Дата возврата");
    return model;
}

QList<Loan> LibraryFacade::getActiveLoans()
{
    QList<Loan> loans;
    QSqlQuery query("SELECT id, readerId, bookId, issueDate, returnDate FROM loans "
                    "WHERE returnDate IS NULL");
    while (query.next()) {
        loans.append(Loan(query.value(0).toInt(),
                          query.value(1).toInt(),
                          query.value(2).toInt(),
                          QDate::fromString(query.value(3).toString(), Qt::ISODate),
                          QDate()));
    }
    return loans;
}

QString LibraryFacade::getBookTitle(int bookId) const
{
    QSqlQuery query;
    query.prepare("SELECT title FROM books WHERE id = ?");
    query.addBindValue(bookId);
    if (query.exec() && query.next())
        return query.value(0).toString();
    return "";
}

QString LibraryFacade::getReaderName(int readerId) const
{
    QSqlQuery query;
    query.prepare("SELECT fullName FROM readers WHERE id = ?");
    query.addBindValue(readerId);
    if (query.exec() && query.next())
        return query.value(0).toString();
    return "";
}

Book LibraryFacade::getBookById(int bookId) const
{
    QSqlQuery query;
    query.prepare("SELECT id, title, author, year, publisherId, available FROM books WHERE id = ?");
    query.addBindValue(bookId);
    if (query.exec() && query.next()) {
        return Book(query.value(0).toInt(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toInt(),
                    query.value(4).toInt(),
                    query.value(5).toBool());
    }
    return Book();
}

void LibraryFacade::populateWithSampleData()
{
    QSqlQuery check;

    // Проверяем, есть ли уже данные в таблице издательств
    check.exec("SELECT COUNT(*) FROM publishers");
    if (check.next() && check.value(0).toInt() > 0) {
        qDebug() << "База данных уже содержит данные, пропускаем заполнение";
        return;
    }

    qDebug() << "Заполнение базы данных тестовыми значениями...";

    // ========== 1. ДОБАВЛЯЕМ ИЗДАТЕЛЬСТВА ==========
    QList<Publisher> publishers = {
        Publisher(0, "Питер", "Санкт-Петербург, Бумажная ул., 12", "+7(812)123-45-67"),
        Publisher(0, "Вильямс", "Москва, ул. Образцова, 11", "+7(495)234-56-78"),
        Publisher(0, "ДМК Пресс", "Москва, Дмитровское ш., 107", "+7(495)345-67-89"),
        Publisher(0, "Эксмо", "Москва, ул. Зорге, 22", "+7(495)456-78-90"),
        Publisher(0, "Наука", "Москва, ул. Профсоюзная, 90", "+7(495)567-89-01")
    };

    for (const Publisher& p : publishers) {
        addPublisher(p);
    }
    qDebug() << "Добавлено издательств:" << publishers.size();

    // Получаем ID добавленных издательств
    QMap<QString, int> publisherIds;
    QSqlQuery query("SELECT id, name FROM publishers");
    while (query.next()) {
        publisherIds[query.value(1).toString()] = query.value(0).toInt();
    }

    // ========== 2. ДОБАВЛЯЕМ КНИГИ ==========
    QList<Book> books = {
        Book(0, "Самоучитель C++", "Шилдт Г.", 2010, publisherIds["Питер"], true),
        Book(0, "Язык программирования C++", "Страуструп Б.", 2015, publisherIds["Вильямс"], true),
        Book(0, "Qt 6 для профессионалов", "Бланшет М.", 2020, publisherIds["ДМК Пресс"], true),
        Book(0, "Паттерны проектирования", "Фримен Э.", 2018, publisherIds["Питер"], true),
        Book(0, "Алгоритмы на C++", "Седжвик Р.", 2016, publisherIds["Вильямс"], true),
        Book(0, "Современный C++", "Майерс С.", 2019, publisherIds["ДМК Пресс"], true),
        Book(0, "STL: стандартная библиотека", "Джосаттис Н.", 2017, publisherIds["Питер"], true),
        Book(0, "Эффективный C++", "Майерс С.", 2015, publisherIds["Вильямс"], true),
        Book(0, "Искусство программирования", "Кнут Д.", 2005, publisherIds["Наука"], true),
        Book(0, "Программирование на C++", "Лафоре Р.", 2014, publisherIds["Питер"], true)
    };

    for (const Book& b : books) {
        addBook(b);
    }
    qDebug() << "Добавлено книг:" << books.size();

    // Получаем ID добавленных книг для последующего использования
    QMap<QString, int> bookIds;
    QSqlQuery bookQuery("SELECT id, title FROM books");
    while (bookQuery.next()) {
        bookIds[bookQuery.value(1).toString()] = bookQuery.value(0).toInt();
    }

    // ========== 3. ДОБАВЛЯЕМ ЧИТАТЕЛЕЙ (через фабрику) ==========
    struct ReaderData {
        int id;
        QString name;
        QString address;
        QString phone;
        ReaderType type;
    };

    QList<ReaderData> readersData = {
        {1001, "Иванов Иван Иванович", "ул. Гастелло, д.15, кв.5", "+7-921-100-01-01", ReaderType::Regular},
        {1002, "Петров Петр Петрович", "Московский пр., д.202, кв.45", "+7-911-105-23-35", ReaderType::Regular},
        {1003, "Сидоров Сергей Сергеевич", "ул. Гастелло, д.17, кв.8", "+7-911-107-07-07", ReaderType::New},
        {1004, "Кузнецова Анна Михайловна", "Невский пр., д.45, кв.12", "+7-921-200-12-34", ReaderType::Premium},
        {1005, "Соколов Дмитрий Алексеевич", "ул. Восстания, д.8, кв.3", "+7-911-300-23-45", ReaderType::Regular},
        {1006, "Попова Елена Владимировна", "Литейный пр., д.32, кв.7", "+7-921-400-34-56", ReaderType::Premium},
        {1007, "Васильев Андрей Петрович", "ул. Рубинштейна, д.12, кв.9", "+7-911-500-45-67", ReaderType::New},
        {1008, "Зайцев Максим Игоревич", "Загородный пр., д.67, кв.2", "+7-921-600-56-78", ReaderType::Regular}
    };

    for (const ReaderData& rd : readersData) {
        Reader* reader = ReaderFactory::createReader(rd.type, rd.id, rd.name, rd.address, rd.phone);
        addReader(reader);  // reader удаляется внутри addReader
    }
    qDebug() << "Добавлено читателей:" << readersData.size();

    // ========== 4. СОЗДАЁМ ВЫДАЧИ КНИГ ==========
    // Некоторые книги уже должны быть выданы для демонстрации

    // Книга "Самоучитель C++" (ID предположительно 1) выдана Иванову
    // Книга "Язык программирования C++" (ID предположительно 2) выдана Петрову и возвращена
    // Книга "Qt 6 для профессионалов" (ID 3) выдана Сидорову и просрочена (была выдана 30 дней назад)

    // Получаем актуальные ID книг
    QSqlQuery idQuery;

    // Выдача 1: книга "Самоучитель C++" читателю Иванов (активная)
    idQuery.exec("SELECT id FROM books WHERE title = 'Самоучитель C++' LIMIT 1");
    if (idQuery.next()) {
        int bookId = idQuery.value(0).toInt();
        issueBook(1001, bookId, QDate::currentDate().addDays(-7));
        qDebug() << "Выдана книга ID" << bookId << "читателю 1001 (Иванов)";
    }

    // Выдача 2: книга "Язык программирования C++" читателю Петров (возвращена)
    idQuery.exec("SELECT id FROM books WHERE title = 'Язык программирования C++' LIMIT 1");
    if (idQuery.next()) {
        int bookId = idQuery.value(0).toInt();
        QDate issueDate = QDate::currentDate().addDays(-15);
        QDate returnDate = QDate::currentDate().addDays(-3);

        // Сначала выдаём
        QSqlQuery insert;
        insert.prepare("INSERT INTO loans (readerId, bookId, issueDate, returnDate) VALUES (?, ?, ?, ?)");
        insert.addBindValue(1002);
        insert.addBindValue(bookId);
        insert.addBindValue(issueDate.toString(Qt::ISODate));
        insert.addBindValue(returnDate.toString(Qt::ISODate));
        insert.exec();

        // Книга должна быть доступна (available=1), так как возвращена
        QSqlQuery update;
        update.prepare("UPDATE books SET available = 1 WHERE id = ?");
        update.addBindValue(bookId);
        update.exec();

        qDebug() << "Книга ID" << bookId << "читателю 1002 (Петров) - возвращена";
    }

    // Выдача 3: книга "Qt 6 для профессионалов" читателю Сидоров (просрочена)
    idQuery.exec("SELECT id FROM books WHERE title = 'Qt 6 для профессионалов' LIMIT 1");
    if (idQuery.next()) {
        int bookId = idQuery.value(0).toInt();
        QDate issueDate = QDate::currentDate().addDays(-30);

        QSqlQuery insert;
        insert.prepare("INSERT INTO loans (readerId, bookId, issueDate, returnDate) VALUES (?, ?, ?, NULL)");
        insert.addBindValue(1003);
        insert.addBindValue(bookId);
        insert.addBindValue(issueDate.toString(Qt::ISODate));
        insert.exec();

        QSqlQuery update;
        update.prepare("UPDATE books SET available = 0 WHERE id = ?");
        update.addBindValue(bookId);
        update.exec();

        qDebug() << "Книга ID" << bookId << "читателю 1003 (Сидоров) - просрочена на 16 дней";
    }

    // Выдача 4: книга "Паттерны проектирования" читателю Кузнецова (Премиум, активная)
    idQuery.exec("SELECT id FROM books WHERE title = 'Паттерны проектирования' LIMIT 1");
    if (idQuery.next()) {
        int bookId = idQuery.value(0).toInt();
        issueBook(1004, bookId, QDate::currentDate().addDays(-3));
        qDebug() << "Книга ID" << bookId << "выдана читателю 1004 (Кузнецова)";
    }

    // Выдача 5: книга "Алгоритмы на C++" читателю Соколов (активная)
    idQuery.exec("SELECT id FROM books WHERE title = 'Алгоритмы на C++' LIMIT 1");
    if (idQuery.next()) {
        int bookId = idQuery.value(0).toInt();
        issueBook(1005, bookId, QDate::currentDate().addDays(-10));
        qDebug() << "Книга ID" << bookId << "выдана читателю 1005 (Соколов)";
    }

    qDebug() << "Заполнение базы данных завершено!";
}
