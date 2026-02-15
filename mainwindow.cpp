#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tiresChb, &QCheckBox::stateChanged, this, &MainWindow::on_tiresChb_checked);
    connect(ui->discsChb, &QCheckBox::stateChanged, this, &MainWindow::on_discsChb_checked);
    connect(ui->cascoChb, &QCheckBox::stateChanged, this, &MainWindow::on_cascoChb_checked);
    connect(ui->osagoChb, &QCheckBox::stateChanged, this, &MainWindow::on_osagoChb_checked);
    connect(ui->condChb, &QCheckBox::stateChanged, this, &MainWindow::on_condChb_checked);
    connect(ui->signChb, &QCheckBox::stateChanged, this, &MainWindow::on_signChb_checked);
    connect(ui->lightsChb, &QCheckBox::stateChanged, this, &MainWindow::on_lightsChb_checked);
    connect(ui->resultBtn, &QPushButton::released, this, &MainWindow::on_resultBtn_released);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::component_unchecked(QPixmap component_image, int component_index){
    if (ui->imageLbl->pixmap().cacheKey() == component_image.cacheKey()){
        ui->imageLbl->clear();
        ui->picked_itemLbl->clear();
    }

    total_price -= componentsPrices[component_index];
    selectedConponents[component_index] = "";
}


void MainWindow::component_checked(QPixmap component_image, int component_index, QString component_name){
    ui->imageLbl->setPixmap(component_image);
    ui->picked_itemLbl->setText(component_name);

    total_price += componentsPrices[component_index];

    selectedConponents[component_index] = component_name;
}


void MainWindow::on_tiresChb_checked(int state){
    QPixmap image(":/images/vidy.jpg");

    if (state == Qt::Checked){
        QString name; name = ui->tiresChb->text();
        component_checked(image, 0, name);
    }
    else{
        component_unchecked(image, 0);
    }
    on_resultBtn_released();

}


void MainWindow::on_discsChb_checked(int state){
    QPixmap image(":/images/discs.jpeg");

    if (state == Qt::Checked){
        QString name; name = ui->discsChb->text();
        component_checked(image, 1, name);
    }
    else{
        component_unchecked(image, 1);
    }
    on_resultBtn_released();
}


void MainWindow::on_cascoChb_checked(int state){
    QPixmap image(":/images/casco.jpeg");

    if (state == Qt::Checked){
        QString name; name = ui->cascoChb->text();
        component_checked(image, 2, name);
    }
    else{
        component_unchecked(image, 2);
    }
    on_resultBtn_released();
}


void MainWindow::on_osagoChb_checked(int state){
    QPixmap image(":/images/osago.png");

    if (state == Qt::Checked){
        QString name; name = ui->osagoChb->text();
        component_checked(image, 3, name);
    }
    else{
        component_unchecked(image, 3);
    }
    on_resultBtn_released();
}


void MainWindow::on_condChb_checked(int state){
    QPixmap image(":/images/cond.jpeg");

    if (state == Qt::Checked){
        QString name; name = ui->condChb->text();
        component_checked(image, 4, name);
    }
    else{
        component_unchecked(image, 4);
    }
    on_resultBtn_released();
}


void MainWindow::on_signChb_checked(int state){
    QPixmap image(":/images/sign.jpeg");

    if (state == Qt::Checked){
        QString name; name = ui->signChb->text();
        component_checked(image, 5, name);
    }
    else{
        component_unchecked(image, 5);
    }
    on_resultBtn_released();
}


void MainWindow::on_lightsChb_checked(int state){
    QPixmap image(":/images/lights.jpeg");

    if (state == Qt::Checked){
        QString name; name = ui->lightsChb->text();
        component_checked(image, 6, name);
    }
    else{
        component_unchecked(image, 6);
    }
    on_resultBtn_released();
}


void MainWindow::on_resultBtn_released(){


    QString text_for_result;
    int compoonent_count = 0;

    for(int i = 0; i < 7; i ++){
        if (selectedConponents[i]!=""){
            QString price; price.setNum(componentsPrices[i]);
            text_for_result += selectedConponents[i] + ": "+price +"\n";
            compoonent_count += 1;
        }
    }
    if (compoonent_count == 7){
        QString total_price_str; total_price_str.setNum(total_price*0.9);
        text_for_result += "\nИтого(скидка 10%): " + total_price_str;
    }
    else{
        QString total_price_str; total_price_str.setNum(total_price);
        text_for_result += "\nИтого: " + total_price_str;
    }

    ui->resultLbl->setText(text_for_result);

}
