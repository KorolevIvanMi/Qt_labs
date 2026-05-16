// Листинг файла calculationfacade.h
#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H


#include <QObject>
#include <memory>
#include "estate.h"
#include "CalcFactory.h"
#include "apartmentcalcfactory.h"
#include "luxuriousapartmentcalcfactory.h"
#include "townhousecalcfactory.h"
#include "cottagecalcfactory.h"

class CalculationFacade : public QObject
{
    Q_OBJECT
public:
    explicit CalculationFacade(QObject *parent = nullptr);

    // Новая версия - не статическая!
    int getCost(Estate *value);

private:
    CalcFactory* getFactoryByType(Estate::EstateType type);
};


#endif // CALCULATIONFACADE_H
