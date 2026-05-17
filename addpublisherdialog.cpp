#include "addpublisherdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "publisher.h"

AddPublisherDialog::AddPublisherDialog(LibraryFacade* facade, QWidget* parent)
    : QDialog(parent), m_facade(facade)
{
    setWindowTitle("Добавить издательство");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_nameEdit = new QLineEdit;
    m_addressEdit = new QLineEdit;
    m_phoneEdit = new QLineEdit;

    formLayout->addRow("Название:", m_nameEdit);
    formLayout->addRow("Адрес:", m_addressEdit);
    formLayout->addRow("Телефон:", m_phoneEdit);

    QPushButton* okBtn = new QPushButton("OK");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &AddPublisherDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void AddPublisherDialog::onAccept()
{
    if (m_nameEdit->text().isEmpty()) return;

    Publisher publisher(0, m_nameEdit->text(), m_addressEdit->text(), m_phoneEdit->text());
    if (m_facade->addPublisher(publisher))
        accept();
}
