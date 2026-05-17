#ifndef LIBRARYFACADE_H
#define LIBRARYFACADE_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QList>
#include "book.h"
#include "reader.h"
#include "loan.h"
#include "publisher.h"

class LibraryFacade
{
private:
    QSqlDatabase m_db;
    bool initDatabase();

public:
    LibraryFacade();
    ~LibraryFacade();

    // Книги
    bool addBook(const Book& book);
    bool updateBook(const Book& book);
    bool deleteBook(int bookId);
    QSqlQueryModel* getAllBooksModel();
    QList<Book> getAllBooks();
    QList<Book> getAvailableBooks();

    // Читатели
    bool addReader(Reader* reader);
    bool updateReader(const Reader& reader);
    bool deleteReader(int readerId);
    QSqlQueryModel* getAllReadersModel();
    QList<Reader*> getAllReaders();
    Reader* getReaderById(int readerId) const;

    // Издательства
    bool addPublisher(const Publisher& publisher);
    bool updatePublisher(const Publisher& publisher);
    bool deletePublisher(int publisherId);
    QSqlQueryModel* getAllPublishersModel();

    // Выдачи
    bool issueBook(int readerId, int bookId, const QDate& issueDate);
    bool returnBook(int loanId, const QDate& returnDate);
    QSqlQueryModel* getAllLoansModel();
    QList<Loan> getActiveLoans();

    // Вспомогательные
    QString getBookTitle(int bookId) const;
    QString getReaderName(int readerId) const;
    Book getBookById(int bookId) const;

    // НОВЫЙ МЕТОД - заполнение базы тестовыми данными
    void populateWithSampleData();
};

#endif // LIBRARYFACADE_H
