#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "estate.h"

class AbstractCalc {
public:
    virtual ~AbstractCalc() {}
    virtual int getCost(Estate *value) = 0;  // теперь не статический!
};


#endif // ABSTRACTCALC_H
