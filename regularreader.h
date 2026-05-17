#ifndef REGULARREADER_H
#define REGULARREADER_H

#include "reader.h"

class RegularReader : public Reader
{
public:
    RegularReader(int id = 0, const QString& fullName = "",
                  const QString& address = "", const QString& phone = "");
    int getMaxBooks() const override;
    int getLoanPeriodDays() const override;
    QString getTypeName() const override;
};

#endif // REGULARREADER_H
