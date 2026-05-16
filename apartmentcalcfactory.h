#ifndef APARTMENTCALCFACTORY_H
#define APARTMENTCALCFACTORY_H

#include "CalcFactory.h"
#include "apartmentcalc.h"

class ApartmentCalcFactory : public CalcFactory {
public:
    AbstractCalc* createCalculator() override {
        return new ApartmentCalc();
    }
};


#endif // APARTMENTCALCFACTORY_H
