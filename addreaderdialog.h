#ifndef ADDREADERDIALOG_H
#define ADDREADERDIALOG_H

#include <QDialog>
#include "libraryfacade.h"

class QLineEdit;
class QSpinBox;
class QComboBox;

class AddReaderDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    QSpinBox* m_idSpin;
    QLineEdit* m_nameEdit;
    QLineEdit* m_addressEdit;
    QLineEdit* m_phoneEdit;
    QComboBox* m_typeCombo;

public:
    AddReaderDialog(LibraryFacade* facade, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // ADDREADERDIALOG_H
