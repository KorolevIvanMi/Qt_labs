#ifndef COTTAGECALC_H
#define COTTAGECALC_H

#include "AbstractCalc.h"

class CottageCalc:public AbstractCalc {
public:
    int getCost(Estate *value) override;  // больше не static
};

#endif // COTTAGECALC_H
