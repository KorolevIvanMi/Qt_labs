#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupData();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupData(){
    QList<QRadioButton*> season_childrens = ui->seasonGb->findChildren<QRadioButton*>();
    QList<QRadioButton*> rods_childrens = ui->rod_typeGb->findChildren<QRadioButton*>();
    QList<QRadioButton*> line_childrens = ui->fishing_line_typeGb->findChildren<QRadioButton*>();
    QList<QRadioButton*> diametrs_childrens = ui->fishing_line_diametrGb->findChildren<QRadioButton*>();

    int season_name_index = 0;
    foreach (QRadioButton* season_radio, season_childrens) {
        season_radio->setText(seasons[season_name_index++]);
        connect(season_radio, &QRadioButton::clicked, this, &MainWindow::on_radio_clicked());
    }

    int rods_type_index = 0;
    foreach (QRadioButton* rode_type_radio, rods_childrens) {
        rode_type_radio->setText(rods_types[rods_type_index++]);
    }

    int line_types_index = 0;
    foreach (QRadioButton* line_type_radio, line_childrens) {
        line_type_radio->setText(line_types[line_types_index++]);
    }

    int diametr_index = 0;
    foreach (QRadioButton* diametr_radio,diametrs_childrens) {
        QString diametr_str; diametr_str.setNum(line_diametr[diametr_index++]);
        diametr_radio->setText(diametr_str);
    }
}
