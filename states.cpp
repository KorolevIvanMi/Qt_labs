#include "states.h"

States::States(QObject *parent) : QObject(parent)
{
    actualData = nullptr;
}

States::~States()
{
    // delete actualData
    if(actualData){
        delete actualData;
        actualData = nullptr;
    }
    // delete and clear: array
    qDeleteAll(array);
    array.clear();
}

// Реализация метода add
void States::add(Estate *value)
{
    if (value == nullptr) {
        return;
    }

    if (actualData != nullptr) {
        array.append(actualData);
    }

    actualData = value;
}

// Реализация метода getActualData
Estate *States::getActualData()
{
    return actualData;
}

// Реализация метода hasStates
bool States::hasStates()
{
    return !array.isEmpty();
}

// Реализация метода undo
void States::undo()
{
    if (!hasStates()) {
        return;
    }

    if (actualData != nullptr) {
        delete actualData;
        actualData = nullptr;
    }

    actualData = array.takeLast();
    emit notifyObservers();
}
