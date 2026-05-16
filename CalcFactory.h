#ifndef CALCFACTORY_H
#define CALCFACTORY_H


#include "AbstractCalc.h"

class CalcFactory {
public:
    virtual ~CalcFactory() {}
    virtual AbstractCalc* createCalculator() = 0;
};


#endif // CALCFACTORY_H
