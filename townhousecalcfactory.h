#ifndef TOWNHOUSECALCFACTORY_H
#define TOWNHOUSECALCFACTORY_H
#include "CalcFactory.h"
#include "townhousecalc.h"

class TownhouseCalcFactory : public CalcFactory {
public:
    AbstractCalc* createCalculator() override {
        return new TownhouseCalc();
    }
};
#endif // TOWNHOUSECALCFACTORY_H
