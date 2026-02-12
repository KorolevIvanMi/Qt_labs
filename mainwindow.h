#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    int Summa(int a, int b);
    int Substruct(int a, int b);
    int Multiply(int a, int b);
    double Devision(int a, int b);
    bool is_numTxts_empty();


    void on_addBtn_clicked();
    void on_subBtn_clicked();
    void on_multBtn_clicked();
    void on_devBtn_clicked();
    void on_numsTxt_changed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H



