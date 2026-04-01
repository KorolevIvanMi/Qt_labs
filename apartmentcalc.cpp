#include "apartmentcalc.h"

// Метод расчета страховки для квартиры эконом-класса
int ApartmentCalc::getCost(Estate *value)
{
    // Проверка на null-указатель
    if (value == nullptr) {
        return -1;
    }

    // Получаем параметры объекта недвижимости
    int age = value->getAge();           // Возраст недвижимости (лет)
    int area = value->getArea();         // Площадь (кв.м)
    int residents = value->getResidents(); // Количество жильцов
    int months = value->getMonths();     // Срок страхования (месяцев)

    // Формула расчета страховки для эконом-класса:
    // Базовая ставка: 50 руб. за кв.м.
    // Корректировка на возраст: -1% за каждый год старше 10 лет (но не более -30%)
    // Корректировка на количество жильцов: +5% за каждого жильца сверх 2-х
    // Итоговая сумма умножается на срок страхования в месяцах

    const int BASE_RATE = 50;           // Базовая ставка за кв.м.

    // Расчет базовой стоимости
    int baseCost = area * BASE_RATE;

    // Корректировка на возраст (уменьшение для старых зданий)
    double ageDiscount = 0.0;
    if (age > 10) {
        ageDiscount = (age - 10) * 0.01;  // 1% за каждый год старше 10
        if (ageDiscount > 0.30) {
            ageDiscount = 0.30;            // Максимальная скидка 30%
        }
    }

    // Корректировка на количество жильцов (увеличение риска)
    double residentsMultiplier = 1.0;
    if (residents > 2) {
        residentsMultiplier = 1.0 + (residents - 2) * 0.05;  // +5% за каждого сверх 2-х
        if (residentsMultiplier > 1.50) {
            residentsMultiplier = 1.50;    // Максимальное увеличение 50%
        }
    }

    // Расчет итоговой стоимости с учетом всех корректировок
    double costWithDiscount = baseCost * (1.0 - ageDiscount);
    double finalCost = costWithDiscount * residentsMultiplier;

    // Умножаем на срок страхования (в месяцах)
    int totalCost = static_cast<int>(finalCost * months);

    return totalCost;
}
