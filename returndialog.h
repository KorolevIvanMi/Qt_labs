#ifndef RETURNDIALOG_H
#define RETURNDIALOG_H

#include <QDialog>
#include "libraryfacade.h"

class QComboBox;
class QDateEdit;

class ReturnDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    QComboBox* m_loanCombo;
    QDateEdit* m_dateEdit;

public:
    ReturnDialog(LibraryFacade* facade, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // RETURNDIALOG_H
