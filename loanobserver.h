#ifndef LOANOBSERVER_H
#define LOANOBSERVER_H

#include <QString>
#include <QList>
#include <QDate>

class LoanObserver
{
public:
    virtual ~LoanObserver() = default;
    virtual void update(int loanId, int readerId, int bookId, const QDate& issueDate) = 0;
};

class OverdueNotifier : public LoanObserver
{
private:
    int m_overdueDays;
public:
    OverdueNotifier(int overdueDays = 14);
    void update(int loanId, int readerId, int bookId, const QDate& issueDate) override;
    void checkAndNotify();
};

class LoanSubject
{
private:
    static LoanSubject* m_instance;
    QList<LoanObserver*> m_observers;
    LoanSubject() = default;

public:
    static LoanSubject* getInstance();
    void attach(LoanObserver* observer);
    void detach(LoanObserver* observer);
    void notify(int loanId, int readerId, int bookId, const QDate& issueDate);
    void notifyAllActive();
};

#endif // LOANOBSERVER_H
