#ifndef LUXURIOUSAPARTMENTCALC_H
#define LUXURIOUSAPARTMENTCALC_H

#include "AbstractCalc.h"

class LuxuriousApartmentCalc:public AbstractCalc {
public:
    int getCost(Estate *value) override;  // больше не static
};

#endif // LUXURIOUSAPARTMENTCALC_H
