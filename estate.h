#ifndef ESTATE_H
#define ESTATE_H
#include <QObject>
class Estate : public QObject
{
    Q_OBJECT
public:
    enum EstateType {
        ECONOM,
        LUXURIOUS,
        TOWN_HOUSE,
        COTTAGE
    };
    explicit Estate(QObject *parent = nullptr);
    // Обновленный конструктор с параметрами
    explicit Estate(int age, int area, int residents, int months,
                    EstateType type, const QString& owner, QObject *parent = nullptr);

    // Функции чтения полей (геттеры)
    int getAge() const;
    int getArea() const;
    int getResidents() const;
    int getMonths() const;
    EstateType getType() const;
    QString getOwner() const;

private:
    int age;
    int area;
    int residents;
    int months;
    EstateType type;
    QString owner;
};
#endif // ESTATE_H
