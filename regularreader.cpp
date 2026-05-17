#include "regularreader.h"

RegularReader::RegularReader(int id, const QString& fullName,
                             const QString& address, const QString& phone)
    : Reader(id, fullName, address, phone) {}

int RegularReader::getMaxBooks() const { return 7; }
int RegularReader::getLoanPeriodDays() const { return 21; }
QString RegularReader::getTypeName() const { return "Постоянный"; }
