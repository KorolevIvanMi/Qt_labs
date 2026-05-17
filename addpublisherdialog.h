#ifndef ADDPUBLISHERDIALOG_H
#define ADDPUBLISHERDIALOG_H

#include <QDialog>
#include "libraryfacade.h"

class QLineEdit;

class AddPublisherDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    QLineEdit* m_nameEdit;
    QLineEdit* m_addressEdit;
    QLineEdit* m_phoneEdit;

public:
    AddPublisherDialog(LibraryFacade* facade, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // ADDPUBLISHERDIALOG_H
