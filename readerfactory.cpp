#include "readerfactory.h"
#include "newreader.h"
#include "regularreader.h"
#include "premiumreader.h"

Reader* ReaderFactory::createReader(ReaderType type, int id,
                                    const QString& fullName,
                                    const QString& address,
                                    const QString& phone)
{
    switch (type) {
    case ReaderType::New:
        return new NewReader(id, fullName, address, phone);
    case ReaderType::Regular:
        return new RegularReader(id, fullName, address, phone);
    case ReaderType::Premium:
        return new PremiumReader(id, fullName, address, phone);
    default:
        return new NewReader(id, fullName, address, phone);
    }
}
