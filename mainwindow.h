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

private:
    Ui::MainWindow *ui;
    QString materials[6] = {
        "Глянцевый",
        "Матовый" ,
        "Сатиновый",
        "Тканевый",
        "Тенсограй",
        "Звёздное небо"
    };
    int material_prices[6]={
        500,
        600,
        700,
        800,
        900,
        1000
    };
};
#endif // MAINWINDOW_H
