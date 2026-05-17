#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "addbookdialog.h"
#include "editbookdialog.h"
#include "addreaderdialog.h"
#include "editreaderdialog.h"
#include "addpublisherdialog.h"
#include "editpublisherdialog.h"
#include "issuedialog.h"
#include "qsqlquery.h"
#include "returndialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentSearchStrategy(nullptr)
    , m_modelFactory(new StandardModelFactory())
    , m_overdueNotifier(new OverdueNotifier(14))
{
    ui->setupUi(this);  // Загружаем форму из .ui файла

    m_facade.populateWithSampleData();
    refreshAllTables();
    LoanSubject::getInstance()->attach(m_overdueNotifier);
    onCheckOverdue();

    // ПОДКЛЮЧАЕМ СИГНАЛЫ ОТ ВИДЖЕТОВ С ФОРМЫ
    connect(ui->addBookBtn, &QPushButton::clicked, this, &MainWindow::onAddBook);
    connect(ui->editBookBtn, &QPushButton::clicked, this, &MainWindow::onEditBook);
    connect(ui->deleteBookBtn, &QPushButton::clicked, this, &MainWindow::onDeleteBook);

    connect(ui->addReaderBtn, &QPushButton::clicked, this, &MainWindow::onAddReader);
    connect(ui->editReaderBtn, &QPushButton::clicked, this, &MainWindow::onEditReader);
    connect(ui->deleteReaderBtn, &QPushButton::clicked, this, &MainWindow::onDeleteReader);

    connect(ui->addPublisherBtn, &QPushButton::clicked, this, &MainWindow::onAddPublisher);
    connect(ui->editPublisherBtn, &QPushButton::clicked, this, &MainWindow::onEditPublisher);
    connect(ui->deletePublisherBtn, &QPushButton::clicked, this, &MainWindow::onDeletePublisher);

    connect(ui->issueBtn, &QPushButton::clicked, this, &MainWindow::onIssueBook);
    connect(ui->returnBtn, &QPushButton::clicked, this, &MainWindow::onReturnBook);
    connect(ui->overdueBtn, &QPushButton::clicked, this, &MainWindow::onCheckOverdue);

    connect(ui->m_searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(ui->m_searchCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::updateSearchStrategy);

    updateSearchStrategy();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_currentSearchStrategy;
    delete m_modelFactory;
    delete m_overdueNotifier;
}

// ========== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ==========

int MainWindow::getSelectedBookId()
{
    QModelIndexList selected = ui->m_booksView->selectionModel()->selectedRows();
    if (selected.isEmpty()) return -1;
    return selected.first().data().toInt();
}

int MainWindow::getSelectedReaderId()
{
    QModelIndexList selected = ui->m_readersView->selectionModel()->selectedRows();
    if (selected.isEmpty()) return -1;
    return selected.first().data().toInt();
}

int MainWindow::getSelectedPublisherId()
{
    QModelIndexList selected = ui->m_publishersView->selectionModel()->selectedRows();
    if (selected.isEmpty()) return -1;
    return selected.first().data().toInt();
}

void MainWindow::updateSearchStrategy()
{
    delete m_currentSearchStrategy;
    int index = ui->m_searchCombo->currentIndex();
    switch (index) {
    case 0: m_currentSearchStrategy = new SearchByTitle(); break;
    case 1: m_currentSearchStrategy = new SearchByAuthor(); break;
    case 2: m_currentSearchStrategy = new SearchByYear(); break;
    default: m_currentSearchStrategy = new SearchByTitle(); break;
    }
}

void MainWindow::refreshAllTables()
{
    refreshBooksTable();
    refreshReadersTable();
    refreshLoansTable();
    refreshPublishersTable();
}

void MainWindow::refreshBooksTable()
{
    QSqlQueryModel* model = m_modelFactory->createBookModel();
    ui->m_booksView->setModel(model);
}

void MainWindow::refreshReadersTable()
{
    QSqlQueryModel* model = m_modelFactory->createReaderModel();
    ui->m_readersView->setModel(model);
}

void MainWindow::refreshLoansTable()
{
    QSqlQueryModel* model = m_modelFactory->createLoanModel();
    ui->m_loansView->setModel(model);
}

void MainWindow::refreshPublishersTable()
{
    QSqlQueryModel* model = m_modelFactory->createPublisherModel();
    ui->m_publishersView->setModel(model);
}

// ========== ОПЕРАЦИИ С КНИГАМИ ==========

void MainWindow::onAddBook()
{
    AddBookDialog dlg(&m_facade, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshBooksTable();
    }
}

void MainWindow::onEditBook()
{
    int bookId = getSelectedBookId();
    if (bookId == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите книгу для редактирования!");
        return;
    }

    Book book = m_facade.getBookById(bookId);
    if (book.getId() == 0) {
        QMessageBox::warning(this, "Ошибка", "Книга не найдена!");
        return;
    }

    EditBookDialog dlg(&m_facade, book, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshBooksTable();
    }
}

void MainWindow::onDeleteBook()
{
    int bookId = getSelectedBookId();
    if (bookId == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите книгу для удаления!");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение", "Удалить книгу?") == QMessageBox::Yes) {
        if (m_facade.deleteBook(bookId)) {
            refreshBooksTable();
        }
    }
}

// ========== ОПЕРАЦИИ С ЧИТАТЕЛЯМИ ==========

void MainWindow::onAddReader()
{
    AddReaderDialog dlg(&m_facade, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshReadersTable();
    }
}

void MainWindow::onEditReader()
{
    int readerId = getSelectedReaderId();
    if (readerId == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите читателя!");
        return;
    }

    Reader* reader = m_facade.getReaderById(readerId);
    if (!reader) {
        QMessageBox::warning(this, "Ошибка", "Читатель не найден!");
        return;
    }

    EditReaderDialog dlg(&m_facade, reader, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshReadersTable();
    }
    delete reader;
}

void MainWindow::onDeleteReader()
{
    int readerId = getSelectedReaderId();
    if (readerId == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите читателя!");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение", "Удалить читателя?") == QMessageBox::Yes) {
        if (m_facade.deleteReader(readerId)) {
            refreshReadersTable();
        }
    }
}

// ========== ОПЕРАЦИИ С ИЗДАТЕЛЬСТВАМИ ==========

void MainWindow::onAddPublisher()
{
    AddPublisherDialog dlg(&m_facade, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshPublishersTable();
    }
}

void MainWindow::onEditPublisher()
{
    int publisherId = getSelectedPublisherId();
    if (publisherId == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите издательство!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, name, address, phone FROM publishers WHERE id = ?");
    query.addBindValue(publisherId);
    if (!query.exec() || !query.next()) return;

    Publisher publisher(query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString());

    EditPublisherDialog dlg(&m_facade, publisher, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshPublishersTable();
    }
}

void MainWindow::onDeletePublisher()
{
    int publisherId = getSelectedPublisherId();
    if (publisherId == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите издательство!");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение", "Удалить издательство?") == QMessageBox::Yes) {
        if (m_facade.deletePublisher(publisherId)) {
            refreshPublishersTable();
            refreshBooksTable();
        }
    }
}

// ========== ВЫДАЧИ ==========

void MainWindow::onIssueBook()
{
    IssueDialog dlg(&m_facade, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshBooksTable();
        refreshLoansTable();
        onCheckOverdue();
    }
}

void MainWindow::onReturnBook()
{
    ReturnDialog dlg(&m_facade, this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshBooksTable();
        refreshLoansTable();
    }
}

// ========== ПОИСК ==========

void MainWindow::onSearch()
{
    if (!m_currentSearchStrategy) return;
    QString keyword = ui->m_searchEdit->text().trimmed();
    if (keyword.isEmpty()) {
        refreshBooksTable();
    } else {
        QSqlQueryModel* result = m_currentSearchStrategy->search(keyword);
        ui->m_booksView->setModel(result);
    }
}

void MainWindow::onCheckOverdue()
{
    m_overdueNotifier->checkAndNotify();
    QMessageBox::information(this, "Проверка просрочек", "Результаты в консоли.");
}
