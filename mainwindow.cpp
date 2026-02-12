#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addBtn, &QPushButton::clicked, this,&MainWindow::on_addBtn_clicked);
    connect(ui->subBtn, &QPushButton::clicked, this,&MainWindow::on_subBtn_clicked);
    connect(ui->multBtn, &QPushButton::clicked, this,&MainWindow::on_multBtn_clicked);
    connect(ui->devBtn, &QPushButton::clicked, this,&MainWindow::on_devBtn_clicked);
    connect(ui->lineNum1, &QLineEdit::textEdited, this, &MainWindow::on_numsTxt_changed);
    connect(ui->lineNum2, &QLineEdit::textEdited, this, &MainWindow::on_numsTxt_changed);
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


int MainWindow::Multiply(int a , int b){
    return a*b;
}


double MainWindow::Devision(int a, int b){
    if (b == 0){
        throw std::runtime_error("Деление на 0");
    }
    return static_cast<double>(a)/static_cast<double>(b);
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


void MainWindow::on_multBtn_clicked(){
    int num1 = ui->lineNum1->text().toInt();
    int num2 = ui->lineNum2->text().toInt();

    int mult = Multiply(num1, num2);
    QString result;
    result.setNum(mult);

    ui->resultEdit->setText(result);
}


void MainWindow::on_devBtn_clicked(){
    int num1 = ui->lineNum1->text().toInt();
    int num2 = ui->lineNum2->text().toInt();
    QString result;
    try{
        double dev = Devision(num1, num2);
        result.setNum(dev);
        ui->resultEdit->setText(result);
    }
    catch(const std::runtime_error& e){
        ui->resultEdit->setText(QString("Ошибка: %1").arg(e.what()));
    }

}

void MainWindow::on_numsTxt_changed(){
    ui->resultEdit->clear();
}

