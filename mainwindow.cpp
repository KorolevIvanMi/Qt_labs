#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->resultBtn, &QPushButton::released, this, &MainWindow::resultBtn_released);
    connect(ui->materialCmb, &QComboBox::currentIndexChanged, this, &MainWindow::material_changed);
    connect(ui->heightTxt, &QLineEdit::textChanged, this, &MainWindow::paramTxt_changed);
    connect(ui->lengthTxt, &QLineEdit::textChanged, this, &MainWindow::paramTxt_changed);

    for(int i = 0 ; i < 6; i++){
        ui->materialCmb->addItem(materials[i]);
    }
    ui->materialPriceTxt->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::is_empty(){
    QString height = ui->heightTxt->text();
    QString length = ui->lengthTxt->text();
    if(height == "" or height == " " or length == "" or length == " "){
        return false;
    }

    return true;
}


void MainWindow::paramTxt_changed(){
    ui->resultLbl->clear();
    if (is_empty()){
        ui->resultBtn->setEnabled(true);
    }
    else{
        ui->resultBtn->setEnabled(false);
    }

}


double MainWindow::count_s(double a, double b){
    return a*b;
}


double MainWindow::count_price(double s, double material_price){
    return s*material_price;
}

void MainWindow::material_changed(int material_index){
    ui->resultLbl->clear();

    int price = material_prices[material_index];
    QString price_str; price_str.setNum(price);

    ui->materialPriceTxt->setText(price_str);
}


QString MainWindow::get_material_by_id(int materail_id){
    return materials[materail_id];
}


void MainWindow::resultBtn_released(){
    double height = ui->heightTxt->text().toDouble();
    double length = ui->lengthTxt->text().toDouble();
    int material_price = ui->materialPriceTxt->text().toInt();
    int material_index = ui->materialCmb->currentIndex();


    double s = count_s(height, length);
    double total_price = count_price(s, material_price);


    QString total_price_str; total_price_str.setNum(total_price);
    QString s_str; s_str.setNum(s);
    QString material_price_str; material_price_str.setNum(material_price);
    QString material_name = get_material_by_id(material_index);

    QString result_txt  =
        "Длина: " + ui->heightTxt->text() +
        "\nШирина: " + ui->lengthTxt->text() +
        "\nПлощадь: " + s_str+
        "\nМатериал: " + material_name +
        "\nЦена материала: " + material_price_str+
        "\nИтого: " + total_price_str;

    ui->resultLbl->setText(result_txt);
}

