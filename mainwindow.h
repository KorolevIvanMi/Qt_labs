#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qradiobutton.h"
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
    QRadioButton* find_active_radio_btn(QList<QRadioButton*>);
    int find_price_by_name(QString, QString[], int[],int );

private:
    Ui::MainWindow *ui;

    QList<QRadioButton*> season_childrens;
    QList<QRadioButton*> rods_childrens;
    QList<QRadioButton*> line_childrens;
    QList<QRadioButton*> diametrs_childrens;

    QString seasons[2] = {
        "Зима",
        "Лето"
    };
    int seasons_price[2]{1000,600};

    QString rods_types[3] = {
        "Инерционная",
        "Безынерционная",
        "Мультипликаторная"
    };
    int rods_types_price[3] = {500, 1000, 1300};

    QString line_types[3] = {
        "Монофильная",
        "Плетёная",
        "Флюрокарбон"
    };
    int line_types_price[3] = {50, 100, 150};

    QString line_diametr[4] = {
        "0.1",
        "0.15",
        "0.2",
        "0.25"
    };
    int line_diametr_price[4] = {20, 30, 40, 50};
    int meters = 0;

private slots:
    void radio_clicked();
    void result_btn_clicked();
    void meters_changed();
};
#endif // MAINWINDOW_H
