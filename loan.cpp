#include "loan.h"

Loan::Loan(int id, int readerId, int bookId,
           const QDate& issueDate, const QDate& returnDate)
    : m_id(id), m_readerId(readerId), m_bookId(bookId),
    m_issueDate(issueDate), m_returnDate(returnDate) {}

int Loan::getId() const { return m_id; }
void Loan::setId(int id) { m_id = id; }
int Loan::getReaderId() const { return m_readerId; }
void Loan::setReaderId(int readerId) { m_readerId = readerId; }
int Loan::getBookId() const { return m_bookId; }
void Loan::setBookId(int bookId) { m_bookId = bookId; }
QDate Loan::getIssueDate() const { return m_issueDate; }
void Loan::setIssueDate(const QDate& issueDate) { m_issueDate = issueDate; }
QDate Loan::getReturnDate() const { return m_returnDate; }
void Loan::setReturnDate(const QDate& returnDate) { m_returnDate = returnDate; }
bool Loan::isReturned() const { return !m_returnDate.isNull(); }
