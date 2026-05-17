#include "editbookdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQuery>

EditBookDialog::EditBookDialog(LibraryFacade* facade, const Book& book, QWidget* parent)
    : QDialog(parent), m_facade(facade), m_book(book)
{
    setWindowTitle("Редактировать книгу");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_titleEdit = new QLineEdit;
    m_titleEdit->setText(m_book.getTitle());
    m_authorEdit = new QLineEdit;
    m_authorEdit->setText(m_book.getAuthor());
    m_yearSpin = new QSpinBox;
    m_yearSpin->setRange(1800, 2100);
    m_yearSpin->setValue(m_book.getYear());
    m_publisherCombo = new QComboBox;

    QSqlQuery query("SELECT id, name FROM publishers");
    while (query.next()) {
        m_publisherCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    // Выбираем текущее издательство
    int index = m_publisherCombo->findData(m_book.getPublisherId());
    if (index >= 0) m_publisherCombo->setCurrentIndex(index);

    formLayout->addRow("Название:", m_titleEdit);
    formLayout->addRow("Автор:", m_authorEdit);
    formLayout->addRow("Год издания:", m_yearSpin);
    formLayout->addRow("Издательство:", m_publisherCombo);

    QPushButton* okBtn = new QPushButton("Сохранить");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &EditBookDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void EditBookDialog::onAccept()
{
    if (m_titleEdit->text().isEmpty() || m_authorEdit->text().isEmpty()) {
        return;
    }

    m_book.setTitle(m_titleEdit->text());
    m_book.setAuthor(m_authorEdit->text());
    m_book.setYear(m_yearSpin->value());
    m_book.setPublisherId(m_publisherCombo->currentData().toInt());

    if (m_facade->updateBook(m_book))
        accept();
}
