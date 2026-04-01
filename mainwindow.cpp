#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btnUndo->setEnabled(false);

    connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));
    connect(ui->btnCalc, &QPushButton::pressed, this, &MainWindow::btnCalcPressed);
    connect(ui->btnUndo, &QPushButton::pressed, this, &MainWindow::btnUndoPressed);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    auto value = info.getActualData();
    if(value!= nullptr){
        fillForm(value);
    }

    ui->btnUndo->setEnabled(info.hasStates());

    value = nullptr;
}

void MainWindow::btnCalcPressed(){
    auto value = processForm();
    showCost(value);
    info.add(value);

    ui->btnUndo->setEnabled(true);

    value = nullptr;
}

void MainWindow::btnUndoPressed(){

    ui->resultLabel->clear();
    info.undo();
}

Estate *MainWindow::processForm(){
    // Получаем возраст недвижимости из поля ввода
    int age = ui->age->text().toInt();

    // Получаем площадь недвижимости из поля ввода
    int area = ui->area->text().toInt();

    // Получаем количество жильцов из поля ввода
    int residents = ui->residents->text().toInt();

    // Получаем владельца из поля ввода
    QString owner = ui->owner->text();

    // Определяем тип недвижимости по выбранному элементу в комбобоксе
    Estate::EstateType type;
    int typeIndex = ui->estateType->currentIndex();
    switch(typeIndex) {
    case 0:  // Квартира эконом-класса
        type = Estate::ECONOM;
        break;
    case 1:  // Элитная квартира
        type = Estate::LUXURIOUS;
        break;
    case 2:  // Таун-хаус
        type = Estate::TOWN_HOUSE;
        break;
    case 3:  // Коттедж
        type = Estate::COTTAGE;
        break;
    default:
        type = Estate::ECONOM;
        break;
    }

    // Определяем срок страхования (в месяцах) по выбранному элементу
    int months;
    int periodIndex = ui->period->currentIndex();
    switch(periodIndex) {
    case 0:  // 6 месяцев
        months = 6;
        break;
    case 1:  // 1 год
        months = 12;
        break;
    case 2:  // 18 месяцев
        months = 18;
        break;
    default:
        months = 12;
        break;
    }

    // Создаем и возвращаем новый объект Estate
    // Примечание: предполагается, что в классе Estate есть конструктор со всеми параметрами
    return new Estate(age, area, residents, months, type, owner, this);

}

void MainWindow::fillForm(Estate *value){
    if (value == nullptr) {
        return;
    }

    // Заполняем поля ввода данными из объекта Estate
    ui->age->setText(QString::number(value->getAge()));
    ui->area->setText(QString::number(value->getArea()));
    ui->residents->setText(QString::number(value->getResidents()));
    ui->owner->setText(value->getOwner());

    // Устанавливаем тип недвижимости в комбобоксе
    switch(value->getType()) {
    case Estate::ECONOM:
        ui->estateType->setCurrentIndex(0);
        break;
    case Estate::LUXURIOUS:
        ui->estateType->setCurrentIndex(1);
        break;
    case Estate::TOWN_HOUSE:
        ui->estateType->setCurrentIndex(2);
        break;
    case Estate::COTTAGE:
        ui->estateType->setCurrentIndex(3);
        break;
    }

    // Устанавливаем срок страхования в комбобоксе
    int months = value->getMonths();
    switch(months) {
    case 6:
        ui->period->setCurrentIndex(0);
        break;
    case 12:
        ui->period->setCurrentIndex(1);
        break;
    case 18:
        ui->period->setCurrentIndex(2);
        break;
    default:
        ui->period->setCurrentIndex(1);  // По умолчанию 12 месяцев
        break;
    }

}

void MainWindow::showCost(Estate *value){
    // Проверяем, что указатель не нулевой
    if (value == nullptr) {
        ui->resultLabel->setText("Ошибка: данные не заполнены");
        return;
    }

    // Вызываем фасад для расчета стоимости страховки
    int cost = CalculationFacade::getCost(value);

    // Проверяем корректность расчета
    if (cost < 0) {
        ui->resultLabel->setText("Ошибка при расчете стоимости страховки");
        return;
    }

    // Формируем и отображаем результат
    QString resultText; resultText.setNum(cost);
    ui->resultLabel->setText(resultText);

}
