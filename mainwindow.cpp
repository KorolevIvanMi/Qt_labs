#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QRadioButton*> season_childrens = ui->seasonGb->findChildren<QRadioButton*>();
    int season_name_index = 0;
    foreach (QRadioButton* season_radio, season_childrens) {
        season_radio->setText(seasons[season_name_index]);
        season_name_index ++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
