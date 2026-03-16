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

int myList::get_element_by_index(int index){
    return collection.at(index);
}
