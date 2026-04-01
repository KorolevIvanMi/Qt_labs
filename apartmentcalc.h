#ifndef APARTMENTCALC_H
#define APARTMENTCALC_H

#include "estate.h"

class ApartmentCalc
{
public:
    // Статический метод для расчета стоимости страховки
    static int getCost(Estate *value);
};

#endif // APARTMENTCALC_H
