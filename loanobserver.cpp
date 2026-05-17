#include "loanobserver.h"
#include <QDebug>
#include <QSqlQuery>

LoanSubject* LoanSubject::m_instance = nullptr;

LoanSubject* LoanSubject::getInstance()
{
    if (!m_instance)
        m_instance = new LoanSubject();
    return m_instance;
}

void LoanSubject::attach(LoanObserver* observer)
{
    if (!m_observers.contains(observer))
        m_observers.append(observer);
}

void LoanSubject::detach(LoanObserver* observer)
{
    m_observers.removeAll(observer);
}

void LoanSubject::notify(int loanId, int readerId, int bookId, const QDate& issueDate)
{
    for (LoanObserver* observer : m_observers)
        observer->update(loanId, readerId, bookId, issueDate);
}

void LoanSubject::notifyAllActive()
{
    QSqlQuery query("SELECT id, readerId, bookId, issueDate FROM loans WHERE returnDate IS NULL");
    while (query.next()) {
        notify(query.value(0).toInt(),
               query.value(1).toInt(),
               query.value(2).toInt(),
               QDate::fromString(query.value(3).toString(), Qt::ISODate));
    }
}

OverdueNotifier::OverdueNotifier(int overdueDays) : m_overdueDays(overdueDays) {}

void OverdueNotifier::update(int loanId, int readerId, int bookId, const QDate& issueDate)
{
    QDate today = QDate::currentDate();
    int daysPassed = issueDate.daysTo(today);
    if (daysPassed > m_overdueDays) {
        qDebug() << "ПРОСРОЧКА! Выдача №" << loanId
                 << ", читатель ID:" << readerId
                 << ", книга ID:" << bookId
                 << ", просрочено на" << (daysPassed - m_overdueDays) << "дней";
    }
}

void OverdueNotifier::checkAndNotify()
{
    QSqlQuery query("SELECT id, readerId, bookId, issueDate FROM loans WHERE returnDate IS NULL");
    while (query.next()) {
        update(query.value(0).toInt(),
               query.value(1).toInt(),
               query.value(2).toInt(),
               QDate::fromString(query.value(3).toString(), Qt::ISODate));
    }
}
