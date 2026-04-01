#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "states.h"
#include "estate.h"
#include "calculationfacade.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    States info;

public slots:
    void update();
private slots:
    void btnCalcPressed();
    void btnUndoPressed();
private:
    Estate* processForm();
    void fillForm(Estate* value);
    void showCost(Estate* value);
};
#endif // MAINWINDOW_H
