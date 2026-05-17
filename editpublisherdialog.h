#ifndef EDITPUBLISHERDIALOG_H
#define EDITPUBLISHERDIALOG_H

#include <QDialog>
#include "libraryfacade.h"
#include "publisher.h"

class QLineEdit;

class EditPublisherDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    Publisher m_publisher;
    QLineEdit* m_nameEdit;
    QLineEdit* m_addressEdit;
    QLineEdit* m_phoneEdit;

public:
    EditPublisherDialog(LibraryFacade* facade, const Publisher& publisher, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // EDITPUBLISHERDIALOG_H
