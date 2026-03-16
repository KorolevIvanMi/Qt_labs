#ifndef MYLIST_H
#define MYLIST_H
#include <QList>

class myList{
private:
    QList<int> collection;
public:
    myList();
    myList(QList<int>);

    int get_element_by_index(int index = 0);
    // bool delete_element_by_index(int index = 0);
    // bool delete_element_by_value(int value = 0);

    // bool add_element_to_end(int value = 0);
    // int summ_element();
    // int summ_chet_element();

    // bool read_from_file(QString);
    // bool save_to_file(QString);
    // bool clear_collection(QString);

    // bool task1();
    // bool task2();
};

#endif // MYLIST_H
