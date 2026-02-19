#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupData();
    connect(ui->resultBtn, &QPushButton::clicked, this, &MainWindow::result_btn_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupData(){
    season_childrens = ui->seasonGb->findChildren<QRadioButton*>();
    rods_childrens = ui->rod_typeGb->findChildren<QRadioButton*>();
    line_childrens = ui->fishing_line_typeGb->findChildren<QRadioButton*>();
    diametrs_childrens = ui->fishing_line_diametrGb->findChildren<QRadioButton*>();

    int season_name_index = 0;
    foreach (QRadioButton* season_radio, season_childrens) {
        season_radio->setText(seasons[season_name_index++]);
        connect(season_radio, &QRadioButton::clicked, this, &MainWindow::radio_clicked);
    }

    int rods_type_index = 0;
    foreach (QRadioButton* rod_type_radio, rods_childrens) {
        rod_type_radio->setText(rods_types[rods_type_index++]);
        connect(rod_type_radio, &QRadioButton::clicked, this, &MainWindow::radio_clicked);
    }

    int line_types_index = 0;
    foreach (QRadioButton* line_type_radio, line_childrens) {
        line_type_radio->setText(line_types[line_types_index++]);
        connect(line_type_radio, &QRadioButton::clicked, this, &MainWindow::radio_clicked);
    }

    int diametr_index = 0;
    foreach (QRadioButton* diametr_radio,diametrs_childrens) {

        diametr_radio->setText( line_diametr[diametr_index++]);
        connect(diametr_radio, &QRadioButton::clicked, this, &MainWindow::radio_clicked);
    }
}


void MainWindow::radio_clicked(){
    ui->result_sumLbl->clear();
}


void MainWindow::result_btn_clicked(){
    QRadioButton* active_season = find_active_radio_btn(season_childrens);
    int season_price = find_price_by_name(active_season->text(), seasons, seasons_price, 2);
    QString season_price_str; season_price_str.setNum(season_price);

    QRadioButton* active_rod_type = find_active_radio_btn(rods_childrens);
    int rod_type = find_price_by_name(active_rod_type->text(), rods_types, rods_types_price, 3);
    QString rod_type_str; rod_type_str.setNum(rod_type);

    QRadioButton* active_line = find_active_radio_btn(line_childrens);
    int line = find_price_by_name(active_line->text(), line_types,line_types_price,3 );
    QString line_str; line_str.setNum(line);

    QRadioButton* active_diametr = find_active_radio_btn(diametrs_childrens);
    int diametr = find_price_by_name(active_diametr->text(), line_diametr, line_diametr_price, 4);
    QString diametr_str; diametr_str.setNum(diametr);

    int summa = season_price + rod_type + line + diametr;
    QString summa_str; summa_str.setNum(summa);

    QString result_txt =
        "Итоговая сумма: \nСезон:" + active_season->text() + "\nцена: " + season_price_str +
        "\nТип катушки: " + active_rod_type->text() + "\nцена: " + rod_type_str +
        "\nТип лески: " + active_line->text() + "\nцена: " + line_str +
        "\nДиаметр лески: " + active_diametr->text() + "\nцена: " + diametr_str +
        "\nИтого: " + summa_str;

    ui->result_sumLbl->setText(result_txt);



}


QRadioButton* MainWindow::find_active_radio_btn(QList<QRadioButton*> list) {
    foreach (QRadioButton* radio, list) {
        if (radio->isChecked()){
            return radio;
        }
    }
    return list[0];
}


int MainWindow::find_price_by_name(QString name ,QString array[], int prices[], int size){
    int res_price = 0;
    for(int i = 0 ; i < size; i ++){
        if (name == array[i]){
            res_price = prices[i];
        }
    }
    return res_price;
}
