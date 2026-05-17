#include "editpublisherdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

EditPublisherDialog::EditPublisherDialog(LibraryFacade* facade, const Publisher& publisher, QWidget* parent)
    : QDialog(parent), m_facade(facade), m_publisher(publisher)
{
    setWindowTitle("Редактировать издательство");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_nameEdit = new QLineEdit;
    m_nameEdit->setText(m_publisher.getName());
    m_addressEdit = new QLineEdit;
    m_addressEdit->setText(m_publisher.getAddress());
    m_phoneEdit = new QLineEdit;
    m_phoneEdit->setText(m_publisher.getPhone());

    formLayout->addRow("Название:", m_nameEdit);
    formLayout->addRow("Адрес:", m_addressEdit);
    formLayout->addRow("Телефон:", m_phoneEdit);

    QPushButton* okBtn = new QPushButton("Сохранить");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &EditPublisherDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void EditPublisherDialog::onAccept()
{
    if (m_nameEdit->text().isEmpty()) return;

    m_publisher.setName(m_nameEdit->text());
    m_publisher.setAddress(m_addressEdit->text());
    m_publisher.setPhone(m_phoneEdit->text());

    if (m_facade->updatePublisher(m_publisher))
        accept();
}
