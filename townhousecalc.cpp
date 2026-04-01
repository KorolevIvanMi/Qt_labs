#include "townhousecalc.h"

int TownhouseCalc::getCost(Estate *value)
{
    if (value == nullptr) {
        return -1;
    }

    int age = value->getAge();
    int area = value->getArea();
    int months = value->getMonths();

    // Для таунхауса средняя ставка
    const int BASE_RATE = 100;  // 100 руб. за кв.м.

    int baseCost = area * BASE_RATE;

    // Для таунхауса учитывается большая площадь и прилегающая территория
    double territoryMultiplier = 1.15;  // +15% за счет придомовой территории

    double finalCost = baseCost * territoryMultiplier;

    // Корректировка на возраст
    if (age > 10) {
        finalCost *= (1.0 - (age - 10) * 0.01);
        if (finalCost < baseCost * 0.7) {
            finalCost = baseCost * 0.7;  // Минимум 70% от базовой
        }
    }

    int totalCost = static_cast<int>(finalCost * months);

    return totalCost;
}
