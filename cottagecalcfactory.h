#ifndef COTTAGECALCFACTORY_H
#define COTTAGECALCFACTORY_H

#include "CalcFactory.h"
#include "cottagecalc.h"

class CottageCalcFactory : public CalcFactory {
public:
    AbstractCalc* createCalculator() override {
        return new CottageCalc();
    }
};


#endif // COTTAGECALCFACTORY_H
