#include "mylist.h"
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
myList::myList() {
    this->collection = {};
}

myList::myList(QList<int> collection){
    if(collection.isEmpty()){
        this->collection = {1,2,3,4,5,6};
    }
    else{
        this->collection = collection;
    }
}


int myList::get_size(){
    return collection.size();
}

QString myList::get_all_data_in_column(){
    QString text;
    for(int i = 0 ; i<collection.size(); i++){
        QString val; val.setNum(collection.at(i));
        text += val + "\n";
    }

    return text;
}

int myList::get_element_by_index(int index){
    return collection.at(index);
}

void myList::delete_element_by_index(int index){
    collection.removeAt(index);
}

void myList::delete_element_by_value(int value){
    collection.removeOne(value);
}

void myList::add_element_to_end(int value){
    collection.append(value);
}

int myList::summ_element(){
    int summa = 0;
    for(int i = 0; i<collection.size(); i++){
        summa += collection.at(i);
    }
    return summa;
}

int myList::summ_chet_element(){
    int summa = 0;
    for(int i = 0; i < collection.size(); i+=2){
        summa += collection.at(i);
    }

    return summa;
}

bool myList::read_from_file(QString file_name){
    QFile file(file_name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        return false;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        bool ok;
        int value = line.toInt(&ok);
        if (ok) {
            collection.append(value);
        }
    }

    file.close();
    return true;
}

bool myList::save_to_file(QString file_name){
    QFile file(file_name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла для записи:" << file.errorString();
        return false;
    }

    QTextStream out(&file);

    for (int i = 0; i < collection.size(); ++i) {
        out << collection[i];
        if (i < collection.size() - 1) {
            out << "\n";
        }
    }

    file.close();
    return true;
}

void myList::clear_collection(){
    collection.clear();
}

bool myList::task1(){
    QList<int> evenPositions;   // Элементы с четных индексов (0, 2, 4...)
    QList<int> oddPositions;    // Элементы с нечетных индексов (1, 3, 5...)

    // Собираем элементы по индексам
    for (int i = 0; i < collection.size(); i++) {
        if (i % 2 == 0) {
            evenPositions.append(collection[i]);  // Добавляем ЗНАЧЕНИЕ!
        } else {
            oddPositions.append(collection[i]);   // Добавляем ЗНАЧЕНИЕ!
        }
    }

    // Очищаем исходную коллекцию
    collection.clear();

    // Добавляем сначала элементы с четных позиций
    collection.append(evenPositions);
    // Затем элементы с нечетных позиций
    collection.append(oddPositions);

    qDebug() << "Результат task1:" << collection;
    return true;
}

int myList::task2(){
    bool flag = false;
    int summa = 0;
    for (int i =0 ; i < collection.size(); i ++){
        if (collection.at(i) < 0){
            flag = true;
        }
        if (flag == true){
            summa +=  abs(collection.at(i));
        }
    }
    return summa;
}
