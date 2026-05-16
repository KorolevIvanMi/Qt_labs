#ifndef LUXURIOUSAPARTMENTCALCFACTORY_H
#define LUXURIOUSAPARTMENTCALCFACTORY_H

#include "CalcFactory.h"
#include "luxuriousapartmentcalc.h"

class LuxuriousApartmentCalcFactory : public CalcFactory {
public:
    AbstractCalc* createCalculator() override {
        return new LuxuriousApartmentCalc();
    }
};


#endif // LUXURIOUSAPARTMENTCALCFACTORY_H
