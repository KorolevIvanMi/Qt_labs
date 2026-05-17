#include "reader.h"

Reader::Reader(int id, const QString& fullName,
               const QString& address, const QString& phone)
    : m_id(id), m_fullName(fullName), m_address(address), m_phone(phone) {}

int Reader::getId() const { return m_id; }
void Reader::setId(int id) { m_id = id; }
QString Reader::getFullName() const { return m_fullName; }
void Reader::setFullName(const QString& fullName) { m_fullName = fullName; }
QString Reader::getAddress() const { return m_address; }
void Reader::setAddress(const QString& address) { m_address = address; }
QString Reader::getPhone() const { return m_phone; }
void Reader::setPhone(const QString& phone) { m_phone = phone; }
