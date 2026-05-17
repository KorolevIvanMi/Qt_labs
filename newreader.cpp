#include "newreader.h"

NewReader::NewReader(int id, const QString& fullName,
                     const QString& address, const QString& phone)
    : Reader(id, fullName, address, phone) {}

int NewReader::getMaxBooks() const { return 3; }
int NewReader::getLoanPeriodDays() const { return 14; }
QString NewReader::getTypeName() const { return "Новый"; }
