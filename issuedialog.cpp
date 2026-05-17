#include "issuedialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>

IssueDialog::IssueDialog(LibraryFacade* facade, QWidget* parent)
    : QDialog(parent), m_facade(facade)
{
    setWindowTitle("Выдача книги");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_readerCombo = new QComboBox;
    m_bookCombo = new QComboBox;
    m_dateEdit = new QDateEdit;
    m_dateEdit->setDate(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);

    QList<Reader*> readers = m_facade->getAllReaders();
    for (Reader* r : readers) {
        m_readerCombo->addItem(r->getFullName() + " (" + r->getTypeName() + ")", r->getId());
        delete r;
    }

    refreshBooks();

    formLayout->addRow("Читатель:", m_readerCombo);
    formLayout->addRow("Книга:", m_bookCombo);
    formLayout->addRow("Дата выдачи:", m_dateEdit);

    QPushButton* okBtn = new QPushButton("Выдать");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &IssueDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void IssueDialog::refreshBooks()
{
    m_bookCombo->clear();
    QList<Book> books = m_facade->getAvailableBooks();
    for (const Book& b : books) {
        m_bookCombo->addItem(b.getTitle() + " - " + b.getAuthor(), b.getId());
    }
}

void IssueDialog::onAccept()
{
    if (m_readerCombo->count() == 0 || m_bookCombo->count() == 0) {
        QMessageBox::warning(this, "Ошибка", "Нет доступных читателей или книг!");
        return;
    }

    int readerId = m_readerCombo->currentData().toInt();
    int bookId = m_bookCombo->currentData().toInt();

    if (m_facade->issueBook(readerId, bookId, m_dateEdit->date()))
        accept();
}
