#include "mylist.h"
#include <QList>

myList::myList() {
    this->collection = {1,2,3,4};
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
