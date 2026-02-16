#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0 ; i < 6; i++){
        ui->materialCmb->addItem(materials[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
