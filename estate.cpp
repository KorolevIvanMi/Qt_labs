#include "estate.h"
#include <QString>


Estate::Estate(int age, int area, int residents, int months,
               EstateType type, const QString& owner, QObject *parent)
    : QObject(parent)  // Вызов конструктора базового класса QObject
{
    // Инициализация всех полей класса
    this->age = age;           // Возраст недвижимости
    this->area = area;         // Площадь недвижимости
    this->residents = residents; // Количество жильцов
    this->months = months;     // Количество месяцев владения/аренды
    this->type = type;         // Тип недвижимости (ECONOM, LUXURIOUS, TOWN_HOUSE, COTTAGE)
    this->owner = owner;       // Владелец недвижимости
}

Estate::Estate(QObject *parent)
    : QObject(parent)
{
    // Инициализация полей значениями по умолчанию
    age = 0;
    area = 0;
    residents = 0;
    months = 0;
    type = ECONOM;
    owner = "";
}

// Функция чтения поля age
int Estate::getAge() const
{
    return age;  // Возвращает возраст недвижимости
}

// Функция чтения поля area
int Estate::getArea() const
{
    return area;  // Возвращает площадь недвижимости
}

// Функция чтения поля residents
int Estate::getResidents() const
{
    return residents;  // Возвращает количество жильцов
}

// Функция чтения поля months
int Estate::getMonths() const
{
    return months;  // Возвращает количество месяцев
}

// Функция чтения поля type
Estate::EstateType Estate::getType() const
{
    return type;  // Возвращает тип недвижимости
}

// Функция чтения поля owner
QString Estate::getOwner() const
{
    return owner;  // Возвращает имя владельца
}
