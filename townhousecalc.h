#ifndef TOWNHOUSECALC_H
#define TOWNHOUSECALC_H

#include "AbstractCalc.h"

class TownhouseCalc:public AbstractCalc {
public:
    int getCost(Estate *value) override;  // больше не static
};

#endif // TOWNHOUSECALC_H
