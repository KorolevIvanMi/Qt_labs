#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mylist.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    myList* collection = new myList({10,2,3,4,5,6,7,8,9});


private slots:
    void show_by_index_released();
    void delete_by_index_released();
    void delete_by_value_released();
    void add_element_to_end_released();
    void summ_element_released();
    void summ_chet_element_released();
};
#endif // MAINWINDOW_H
