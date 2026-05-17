#include "publisher.h"

Publisher::Publisher(int id, const QString& name,
                     const QString& address, const QString& phone)
    : m_id(id), m_name(name), m_address(address), m_phone(phone) {}

int Publisher::getId() const { return m_id; }
void Publisher::setId(int id) { m_id = id; }
QString Publisher::getName() const { return m_name; }
void Publisher::setName(const QString& name) { m_name = name; }
QString Publisher::getAddress() const { return m_address; }
void Publisher::setAddress(const QString& address) { m_address = address; }
QString Publisher::getPhone() const { return m_phone; }
void Publisher::setPhone(const QString& phone) { m_phone = phone; }
