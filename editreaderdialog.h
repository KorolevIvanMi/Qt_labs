#ifndef EDITREADERDIALOG_H
#define EDITREADERDIALOG_H

#include <QDialog>
#include "libraryfacade.h"
#include "reader.h"

class QLineEdit;
class QSpinBox;
class QComboBox;

class EditReaderDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    Reader* m_reader;
    QSpinBox* m_idSpin;
    QLineEdit* m_nameEdit;
    QLineEdit* m_addressEdit;
    QLineEdit* m_phoneEdit;
    QComboBox* m_typeCombo;

public:
    EditReaderDialog(LibraryFacade* facade, Reader* reader, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // EDITREADERDIALOG_H
