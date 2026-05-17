#ifndef NEWREADER_H
#define NEWREADER_H

#include "reader.h"

class NewReader : public Reader
{
public:
    NewReader(int id = 0, const QString& fullName = "",
              const QString& address = "", const QString& phone = "");
    int getMaxBooks() const override;
    int getLoanPeriodDays() const override;
    QString getTypeName() const override;
};

#endif // NEWREADER_H
