#ifndef ISSUEDIALOG_H
#define ISSUEDIALOG_H

#include <QDialog>
#include "libraryfacade.h"

class QComboBox;
class QDateEdit;

class IssueDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    QComboBox* m_readerCombo;
    QComboBox* m_bookCombo;
    QDateEdit* m_dateEdit;

    void refreshBooks();

public:
    IssueDialog(LibraryFacade* facade, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // ISSUEDIALOG_H
