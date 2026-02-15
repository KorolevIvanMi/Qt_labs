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

    void on_tiresChb_checked(int state);
    void on_discsChb_checked(int state);
    void on_cascoChb_checked(int state);
    void on_osagoChb_checked(int state);
    void on_condChb_checked(int state);
    void on_signChb_checked(int state);
    void on_lightsChb_checked(int state);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
