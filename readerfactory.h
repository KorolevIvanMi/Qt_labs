#ifndef READERFACTORY_H
#define READERFACTORY_H

#include <QString>
#include "reader.h"

enum class ReaderType { New, Regular, Premium };

class ReaderFactory
{
public:
    static Reader* createReader(ReaderType type, int id,
                                const QString& fullName,
                                const QString& address,
                                const QString& phone);
};

#endif // READERFACTORY_H
