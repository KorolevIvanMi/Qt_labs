#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include "libraryfacade.h"

class QLineEdit;
class QSpinBox;
class QComboBox;

class AddBookDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    QLineEdit* m_titleEdit;
    QLineEdit* m_authorEdit;
    QSpinBox* m_yearSpin;
    QComboBox* m_publisherCombo;

public:
    AddBookDialog(LibraryFacade* facade, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // ADDBOOKDIALOG_H
