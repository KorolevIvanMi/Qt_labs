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

    void SetupData();

private:
    Ui::MainWindow *ui;
    QString seasons[2] = {
        "Зима",
        "Лето"
    };
    QString rods_types[3] = {
        "Инерционная",
        "Безынерционная",
        "Мультипликаторная"
    };
    QString line_types[3] = {
        "Монофильная",
        "Плетёная",
        "Флюрокарбон"
    };
    float line_diametr[4] = {
        0.1,
        0.15,
        0.2,
        0.25
    };

private slots:
    void on_groubBox_clicked();
};
#endif // MAINWINDOW_H
