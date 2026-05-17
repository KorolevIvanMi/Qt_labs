#ifndef PREMIUMREADER_H
#define PREMIUMREADER_H

#include "reader.h"

class PremiumReader : public Reader
{
public:
    PremiumReader(int id = 0, const QString& fullName = "",
                  const QString& address = "", const QString& phone = "");
    int getMaxBooks() const override;
    int getLoanPeriodDays() const override;
    QString getTypeName() const override;
};

#endif // PREMIUMREADER_H
