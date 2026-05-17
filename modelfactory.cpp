#include "modelfactory.h"
#include <QSqlQuery>

QSqlQueryModel* StandardModelFactory::createBookModel() const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, title, author, year, "
                    "CASE WHEN available=1 THEN 'В наличии' ELSE 'Выдана' END as status "
                    "FROM books");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Автор");
    model->setHeaderData(3, Qt::Horizontal, "Год");
    model->setHeaderData(4, Qt::Horizontal, "Статус");
    return model;
}

QSqlQueryModel* StandardModelFactory::createReaderModel() const
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

QSqlQueryModel* StandardModelFactory::createLoanModel() const
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

QSqlQueryModel* StandardModelFactory::createPublisherModel() const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, address, phone FROM publishers");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Адрес");
    model->setHeaderData(3, Qt::Horizontal, "Телефон");
    return model;
}
