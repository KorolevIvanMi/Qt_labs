#ifndef APARTMENTCALC_H
#define APARTMENTCALC_H

#include "AbstractCalc.h"

class ApartmentCalc:public AbstractCalc {
public:
    int getCost(Estate *value) override;  // больше не static
};

#endif // APARTMENTCALC_H
