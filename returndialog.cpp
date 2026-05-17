#include "returndialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>

ReturnDialog::ReturnDialog(LibraryFacade* facade, QWidget* parent)
    : QDialog(parent), m_facade(facade)
{
    setWindowTitle("Возврат книги");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_loanCombo = new QComboBox;
    m_dateEdit = new QDateEdit;
    m_dateEdit->setDate(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);

    QSqlQuery query("SELECT l.id, r.fullName, b.title "
                    "FROM loans l "
                    "JOIN readers r ON l.readerId = r.id "
                    "JOIN books b ON l.bookId = b.id "
                    "WHERE l.returnDate IS NULL");
    while (query.next()) {
        QString text = QString("%1 - %2: %3").arg(query.value(0).toInt())
                           .arg(query.value(1).toString())
                           .arg(query.value(2).toString());
        m_loanCombo->addItem(text, query.value(0).toInt());
    }

    formLayout->addRow("Выдача:", m_loanCombo);
    formLayout->addRow("Дата возврата:", m_dateEdit);

    QPushButton* okBtn = new QPushButton("Вернуть");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &ReturnDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void ReturnDialog::onAccept()
{
    if (m_loanCombo->count() == 0) {
        QMessageBox::warning(this, "Ошибка", "Нет активных выдач!");
        return;
    }

    int loanId = m_loanCombo->currentData().toInt();
    if (m_facade->returnBook(loanId, m_dateEdit->date()))
        accept();
}
