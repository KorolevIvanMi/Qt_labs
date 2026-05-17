#ifndef LOAN_H
#define LOAN_H

#include <QDate>

class Loan
{
private:
    int m_id;
    int m_readerId;
    int m_bookId;
    QDate m_issueDate;
    QDate m_returnDate;

public:
    Loan(int id = 0, int readerId = 0, int bookId = 0,
         const QDate& issueDate = QDate::currentDate(), const QDate& returnDate = QDate());

    int getId() const;
    void setId(int id);
    int getReaderId() const;
    void setReaderId(int readerId);
    int getBookId() const;
    void setBookId(int bookId);
    QDate getIssueDate() const;
    void setIssueDate(const QDate& issueDate);
    QDate getReturnDate() const;
    void setReturnDate(const QDate& returnDate);
    bool isReturned() const;
};

#endif // LOAN_H
