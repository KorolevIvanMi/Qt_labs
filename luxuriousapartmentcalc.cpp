#include "luxuriousapartmentcalc.h"

int LuxuriousApartmentCalc::getCost(Estate *value)
{
    if (value == nullptr) {
        return -1;
    }

    int age = value->getAge();
    int area = value->getArea();
    int months = value->getMonths();

    // Для люксовых квартир повышенная ставка
    const int BASE_RATE = 150;  // 150 руб. за кв.м.

    int baseCost = area * BASE_RATE;

    // Скидка на возраст меньше (престижные дома лучше сохраняются)
    double ageDiscount = 0.0;
    if (age > 15) {
        ageDiscount = (age - 15) * 0.005;  // 0.5% за каждый год старше 15
        if (ageDiscount > 0.15) {
            ageDiscount = 0.15;             // Максимальная скидка 15%
        }
    }

    double finalCost = baseCost * (1.0 - ageDiscount);
    int totalCost = static_cast<int>(finalCost * months);

    return totalCost;
}
