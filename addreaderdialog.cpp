#include "addreaderdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include "readerfactory.h"

AddReaderDialog::AddReaderDialog(LibraryFacade* facade, QWidget* parent)
    : QDialog(parent), m_facade(facade)
{
    setWindowTitle("Добавить читателя");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_idSpin = new QSpinBox;
    m_idSpin->setRange(1, 999999);
    m_nameEdit = new QLineEdit;
    m_addressEdit = new QLineEdit;
    m_phoneEdit = new QLineEdit;
    m_typeCombo = new QComboBox;
    m_typeCombo->addItems({"Новый", "Постоянный", "Премиум"});

    formLayout->addRow("№ читательского билета:", m_idSpin);
    formLayout->addRow("ФИО:", m_nameEdit);
    formLayout->addRow("Адрес:", m_addressEdit);
    formLayout->addRow("Телефон:", m_phoneEdit);
    formLayout->addRow("Категория:", m_typeCombo);

    QPushButton* okBtn = new QPushButton("OK");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &AddReaderDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void AddReaderDialog::onAccept()
{
    if (m_nameEdit->text().isEmpty()) return;

    ReaderType type;
    int idx = m_typeCombo->currentIndex();
    switch (idx) {
    case 0: type = ReaderType::New; break;
    case 1: type = ReaderType::Regular; break;
    default: type = ReaderType::Premium; break;
    }

    Reader* reader = ReaderFactory::createReader(type, m_idSpin->value(),
                                                 m_nameEdit->text(),
                                                 m_addressEdit->text(),
                                                 m_phoneEdit->text());
    if (m_facade->addReader(reader))
        accept();
    else
        delete reader;
}
