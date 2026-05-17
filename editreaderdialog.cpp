#include "editreaderdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include "readerfactory.h"

EditReaderDialog::EditReaderDialog(LibraryFacade* facade, Reader* reader, QWidget* parent)
    : QDialog(parent), m_facade(facade), m_reader(reader)
{
    setWindowTitle("Редактировать читателя");
    setMinimumWidth(400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout;

    m_idSpin = new QSpinBox;
    m_idSpin->setRange(1, 999999);
    m_idSpin->setValue(m_reader->getId());
    m_idSpin->setEnabled(false);  // ID нельзя менять

    m_nameEdit = new QLineEdit;
    m_nameEdit->setText(m_reader->getFullName());
    m_addressEdit = new QLineEdit;
    m_addressEdit->setText(m_reader->getAddress());
    m_phoneEdit = new QLineEdit;
    m_phoneEdit->setText(m_reader->getPhone());
    m_typeCombo = new QComboBox;
    m_typeCombo->addItems({"Новый", "Постоянный", "Премиум"});

    // Выбираем текущий тип
    QString currentType = m_reader->getTypeName();
    int index = m_typeCombo->findText(currentType);
    if (index >= 0) m_typeCombo->setCurrentIndex(index);

    formLayout->addRow("№ читательского билета:", m_idSpin);
    formLayout->addRow("ФИО:", m_nameEdit);
    formLayout->addRow("Адрес:", m_addressEdit);
    formLayout->addRow("Телефон:", m_phoneEdit);
    formLayout->addRow("Категория:", m_typeCombo);

    QPushButton* okBtn = new QPushButton("Сохранить");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    connect(okBtn, &QPushButton::clicked, this, &EditReaderDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cancelBtn);
}

void EditReaderDialog::onAccept()
{
    if (m_nameEdit->text().isEmpty()) return;

    // Создаём нового читателя с обновлёнными данными
    ReaderType type;
    int idx = m_typeCombo->currentIndex();
    switch (idx) {
    case 0: type = ReaderType::New; break;
    case 1: type = ReaderType::Regular; break;
    default: type = ReaderType::Premium; break;
    }

    Reader* updatedReader = ReaderFactory::createReader(
        type, m_idSpin->value(), m_nameEdit->text(),
        m_addressEdit->text(), m_phoneEdit->text());

    if (m_facade->updateReader(*updatedReader)) {
        delete updatedReader;
        accept();
    } else {
        delete updatedReader;
    }
}
