#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mylist.h"

#include <QList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString text = collection->get_all_data_in_column();
    ui->startCollectionTxt->setText(text);
    connect(ui->showByIndexBtn, &QPushButton::released, this, &MainWindow::show_by_index_released);
    connect(ui->deleteByIndexBtn, &QPushButton::released, this, &MainWindow::delete_by_index_released);
    connect(ui->deleteByValueBtn, &QPushButton::released, this, &MainWindow::delete_by_value_released);
    connect(ui->addElementBtn, &QPushButton::released, this, &MainWindow::add_element_to_end_released);
    connect(ui->summElementBtn, &QPushButton::released, this, &MainWindow::summ_element_released);
    connect(ui->summChetElementBtn, &QPushButton::released, this, &MainWindow::summ_chet_element_released);
    connect(ui->readFromFileBtn, &QPushButton::released, this, &MainWindow::read_data_from_file);
    connect(ui->saveToFileBtn, &QPushButton::released, this, &MainWindow::save_data_to_file);
    connect(ui->clearColletionBtn, &QPushButton::released, this, &MainWindow::clear_collection_released);
    connect(ui->task1Btn, &QPushButton::released, this, &MainWindow::task1);
    connect(ui->task2Btn, &QPushButton::released, this, &MainWindow::task2);
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
    ui->endCollectionTxt->setText(val);
}

void MainWindow::delete_by_index_released(){
    int index = ui->elementIndexTxt->text().toInt();
    collection->delete_element_by_index(index);
    QString text = collection->get_all_data_in_column();
    ui->endCollectionTxt->setText(text);
}

void MainWindow::delete_by_value_released(){
    int value = ui->elementValueTxt->text().toInt();
    collection->delete_element_by_value(value);
    QString text = collection->get_all_data_in_column();
    ui->endCollectionTxt->setText(text);
}

void MainWindow::add_element_to_end_released(){
    int value = ui->elementValueTxt->text().toInt();
    collection->add_element_to_end(value);
    QString text = collection->get_all_data_in_column();
    ui->endCollectionTxt->setText(text);
}

void MainWindow::summ_element_released(){
    int summa = collection->summ_element();
    QString val; val.setNum(summa);
    ui->summTxt->setText(val);
}

void MainWindow::summ_chet_element_released(){
    int summa = collection->summ_chet_element();
    QString val; val.setNum(summa);
    ui->summTxt->setText(val);
}

void MainWindow::read_data_from_file(){
    myList* new_collection = new myList();
    new_collection->read_from_file("/home/ivankorolev/MyProjects/For_study/OOP_Qt_Labs/collection.txt");
    delete collection;
    collection = new_collection;


    QString text = collection->get_all_data_in_column();
    ui->startCollectionTxt->setText(text);
}

void MainWindow::save_data_to_file(){
    collection->save_to_file("/home/ivankorolev/MyProjects/For_study/OOP_Qt_Labs/collection.txt");
}

void MainWindow::clear_collection_released(){
    collection->clear_collection();

    QString text = collection->get_all_data_in_column();
    ui->startCollectionTxt->setText(text);
}

void MainWindow::task1(){
    collection->task1();
    QString text = collection->get_all_data_in_column();
    ui->endCollectionTxt->setText(text);
}

void MainWindow::task2(){
    int summa = collection->task2();
    QString val; val.setNum(summa);
    ui->endCollectionTxt->setText(val);
}
