#include "calculationfacade.h"

CalculationFacade::CalculationFacade(QObject *parent) : QObject(parent)
{
}

CalcFactory* CalculationFacade::getFactoryByType(Estate::EstateType type)
{
    switch (type) {
    case Estate::EstateType::ECONOM:
        return new ApartmentCalcFactory();
    case Estate::EstateType::LUXURIOUS:
        return new LuxuriousApartmentCalcFactory();
    case Estate::EstateType::TOWN_HOUSE:
        return new TownhouseCalcFactory();
    case Estate::EstateType::COTTAGE:
        return new CottageCalcFactory();
    default:
        return nullptr;
    }
}

int CalculationFacade::getCost(Estate *value)
{
    // Получаем нужную фабрику по типу
    CalcFactory* factory = getFactoryByType(value->getType());
    if (!factory) {
        return -1;
    }

    // Фабрика создаёт объект-калькулятор
    AbstractCalc* calculator = factory->createCalculator();

    // Вызываем метод у созданного объекта
    int cost = calculator->getCost(value);

    // Чистим память
    delete calculator;
    delete factory;

    return cost;
}
