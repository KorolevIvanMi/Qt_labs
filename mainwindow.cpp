#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mylist.h"

#include <QList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->showByIndexBtn, &QPushButton::released, this, &MainWindow::show_by_index_released);
}

MainWindow::~MainWindow()
{
    delete collection;
    delete ui;
}

void MainWindow::show_by_index_released(){
    int index = ui->elementIndexTxt->text().toInt();
    int value = collection->get_element_by_index(index);
    QString val; val.setNum(value);
    ui->startCollectionTxt->setText(val);
}
