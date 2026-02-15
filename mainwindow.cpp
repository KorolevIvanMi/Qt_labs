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


void MainWindow::on_tiresChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/vidy.jpg");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[0];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[0] = name;

    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[0];
        selectedConponents[0] = "";
    }

}


void MainWindow::on_discsChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/discs.jpeg");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[1];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[1] = name;

    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[1];
        selectedConponents[1] = "";
    }
}


void MainWindow::on_cascoChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/casco.jpeg");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[2];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[2] = name;
    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[2];
        selectedConponents[2] = "";
    }
}


void MainWindow::on_osagoChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/osago.png");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[3];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[3] = name;
    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[3];
        selectedConponents[3] = "";
    }
}


void MainWindow::on_condChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/cond.jpeg");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[4];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[4] = name;
    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[4];
        selectedConponents[4] = "";
    }
}


void MainWindow::on_signChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/sign.jpeg");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[5];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[5] = name;
    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[5];
        selectedConponents[5] = "";
    }
}


void MainWindow::on_lightsChb_checked(int state){
    QPixmap image("/home/ivankorolev/Изображения/lights.jpeg");

    if (state == Qt::Checked){
        ui->imageLbl->setPixmap(image);

        total_price += componentsPrices[6];

        QString name;
        name = ui->tiresChb->text();
        selectedConponents[6] = name;
    }
    else{
        if (ui->imageLbl->pixmap().cacheKey() == image.cacheKey()){
            ui->imageLbl->clear();
        }
        total_price -= componentsPrices[6];
        selectedConponents[6] = "";
    }
}


void MainWindow::on_resultBtn_released(){
    QString total_price_str; total_price_str.setNum(total_price);
    ui->resultLbl->setText(total_price_str);
}
