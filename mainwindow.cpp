#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addBtn, &QPushButton::clicked, this,
            &MainWindow::on_addBtn_clicked);

    connect(ui->subBtn, &QPushButton::clicked, this,
            &MainWindow::on_subBtn_clicked);


}


MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::Summa(int a, int b){
    return a + b;
}


int MainWindow::Substruct(int a, int b){
    return a-b;
}


void MainWindow::on_addBtn_clicked(){
    int num1 = ui->lineNum1->text().toInt();
    int num2 = ui->lineNum2->text().toInt();

    int summa = Summa(num1, num2);
    QString result;
    result.setNum(summa);

    ui->resultEdit->setText(result);

}


void MainWindow::on_subBtn_clicked(){
    int num1 = ui->lineNum1->text().toInt();
    int num2 = ui->lineNum2->text().toInt();

    int sub = Substruct(num1, num2);
    QString result;
    result.setNum(sub);

    ui->resultEdit->setText(result);
}


