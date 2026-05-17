#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libraryfacade.h"
#include "searchstrategy.h"
#include "modelfactory.h"
#include "loanobserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    LibraryFacade m_facade;
    SearchStrategy* m_currentSearchStrategy;
    ModelFactory* m_modelFactory;
    OverdueNotifier* m_overdueNotifier;

    int getSelectedBookId();
    int getSelectedReaderId();
    int getSelectedPublisherId();

    void refreshAllTables();
    void refreshBooksTable();
    void refreshReadersTable();
    void refreshLoansTable();
    void refreshPublishersTable();
    void updateSearchStrategy();

private slots:
    void onAddBook();
    void onEditBook();
    void onDeleteBook();

    void onAddReader();
    void onEditReader();
    void onDeleteReader();

    void onAddPublisher();
    void onEditPublisher();
    void onDeletePublisher();

    void onIssueBook();
    void onReturnBook();

    void onSearch();
    void onCheckOverdue();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
