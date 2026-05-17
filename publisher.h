#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QString>

class Publisher
{
private:
    int m_id;
    QString m_name;
    QString m_address;
    QString m_phone;

public:
    Publisher(int id = 0, const QString& name = "",
              const QString& address = "", const QString& phone = "");

    int getId() const;
    void setId(int id);
    QString getName() const;
    void setName(const QString& name);
    QString getAddress() const;
    void setAddress(const QString& address);
    QString getPhone() const;
    void setPhone(const QString& phone);
};

#endif // PUBLISHER_H
