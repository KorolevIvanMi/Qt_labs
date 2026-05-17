#ifndef READER_H
#define READER_H

#include <QString>

// Абстрактный класс читателя
class Reader
{
protected:
    int m_id;               // Номер читательского билета
    QString m_fullName;     // ФИО читателя
    QString m_address;      // Адрес
    QString m_phone;        // Телефон

public:
    Reader(int id = 0, const QString& fullName = "",
           const QString& address = "", const QString& phone = "");
    virtual ~Reader() = default;

    // Геттеры и сеттеры
    int getId() const;
    void setId(int id);
    QString getFullName() const;
    void setFullName(const QString& fullName);
    QString getAddress() const;
    void setAddress(const QString& address);
    QString getPhone() const;
    void setPhone(const QString& phone);

    // Виртуальные методы – особенности типа читателя
    virtual int getMaxBooks() const = 0;       // макс. кол-во книг
    virtual int getLoanPeriodDays() const = 0; // срок выдачи в днях
    virtual QString getTypeName() const = 0;   // название типа
};

#endif // READER_H
