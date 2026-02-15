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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tiresChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/vidy.jpg");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }

}


void MainWindow::on_discsChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/discs.jpeg");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }
}


void MainWindow::on_cascoChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/casco.jpeg");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }
}


void MainWindow::on_osagoChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/osago.png");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }
}


void MainWindow::on_condChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/cond.jpeg");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }
}


void MainWindow::on_signChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/sign.jpeg");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }
}


void MainWindow::on_lightsChb_checked(int state){
    if (state == Qt::Checked){
        QPixmap image("/home/ivankorolev/Изображения/lights.jpeg");
        ui->imageLbl->setPixmap(image);
    }
    else{
        ui->imageLbl->clear();
    }
}

