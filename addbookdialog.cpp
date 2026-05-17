#include "addbookdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQuery>
#include "book.h"

AddBookDialog::AddBookDialog(LibraryFacade* facade, QWidget* parent)
    : QDialog(parent), m_facade(facade)
{
    setWindowTitle("Добавить книгу");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_titleEdit = new QLineEdit;
    m_authorEdit = new QLineEdit;
    m_yearSpin = new QSpinBox;
    m_yearSpin->setRange(1800, 2100);
    m_yearSpin->setValue(2024);
    m_publisherCombo = new QComboBox;

    QSqlQuery query("SELECT id, name FROM publishers");
    while (query.next())
        m_publisherCombo->addItem(query.value(1).toString(), query.value(0).toInt());

    formLayout->addRow("Название:", m_titleEdit);
    formLayout->addRow("Автор:", m_authorEdit);
    formLayout->addRow("Год издания:", m_yearSpin);
    formLayout->addRow("Издательство:", m_publisherCombo);

    QPushButton* okBtn = new QPushButton("OK");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &AddBookDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void AddBookDialog::onAccept()
{
    if (m_titleEdit->text().isEmpty() || m_authorEdit->text().isEmpty()) {
        return;
    }

    Book book(0, m_titleEdit->text(), m_authorEdit->text(),
              m_yearSpin->value(), m_publisherCombo->currentData().toInt(), true);
    if (m_facade->addBook(book))
        accept();
}
