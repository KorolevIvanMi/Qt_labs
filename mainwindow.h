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
    void on_resultBtn_released();

    void component_unchecked(QPixmap component_image, int component_index);
    void component_checked(QPixmap component_image, int component_index, QString component_name);


private:
    Ui::MainWindow *ui;
    QString selectedConponents[7];
    int componentsPrices[7] = {
        1000, 1500, 2000, 500, 600, 5000, 2499
    };
    int total_price = 20000;

};
#endif // MAINWINDOW_H
