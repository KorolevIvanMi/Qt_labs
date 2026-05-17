#include "premiumreader.h"

PremiumReader::PremiumReader(int id, const QString& fullName,
                             const QString& address, const QString& phone)
    : Reader(id, fullName, address, phone) {}

int PremiumReader::getMaxBooks() const { return 15; }
int PremiumReader::getLoanPeriodDays() const { return 30; }
QString PremiumReader::getTypeName() const { return "Премиум"; }
