#include "cottagecalc.h"

int CottageCalc::getCost(Estate *value)
{
    if (value == nullptr) {
        return -1;
    }

    int age = value->getAge();
    int area = value->getArea();
    int months = value->getMonths();

    // Для коттеджа повышенная ставка из-за большой площади и особых рисков
    const int BASE_RATE = 120;  // 120 руб. за кв.м.

    int baseCost = area * BASE_RATE;

    // Учет особенностей коттеджа
    double cottageMultiplier = 1.25;  // +25% за счет придомовой территории и инженерных систем

    double finalCost = baseCost * cottageMultiplier;

    // Возрастная корректировка
    if (age > 5) {
        finalCost *= (1.0 - (age - 5) * 0.008);
        if (finalCost < baseCost * 0.6) {
            finalCost = baseCost * 0.6;  // Минимум 60% от базовой
        }
    }

    int totalCost = static_cast<int>(finalCost * months);

    return totalCost;
}
