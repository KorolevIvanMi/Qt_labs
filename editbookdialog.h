#ifndef EDITBOOKDIALOG_H
#define EDITBOOKDIALOG_H

#include <QDialog>
#include "libraryfacade.h"
#include "book.h"

class QLineEdit;
class QSpinBox;
class QComboBox;

class EditBookDialog : public QDialog
{
    Q_OBJECT
private:
    LibraryFacade* m_facade;
    Book m_book;
    QLineEdit* m_titleEdit;
    QLineEdit* m_authorEdit;
    QSpinBox* m_yearSpin;
    QComboBox* m_publisherCombo;

public:
    EditBookDialog(LibraryFacade* facade, const Book& book, QWidget* parent = nullptr);

private slots:
    void onAccept();
};

#endif // EDITBOOKDIALOG_H
