#pragma once
#include "Time.h"
#include <string>

using namespace std;

class Bill
{
private:
    // Прізвище платника та номер телефону.
    string surname;
    string phoneNumber;

    // Тариф за хвилину та знижка у відсотках.
    double tariff;
    double discount;

    // Час початку та закінчення телефонної розмови.
    Time startTime;
    Time endTime;

    // Розрахована сума до оплати в гривнях.
    double amount;

    // Перевіряє правильність тарифу.
    bool IsValidTariff(double value) const;

    // Перевіряє правильність знижки.
    bool IsValidDiscount(double value) const;

    // Перевіряє допустимі символи номера телефону.
    bool IsValidPhone(const string& value) const;

    // Обчислює суму оплати за розмову.
    void CalculateAmount();

public:
    // Створює платіж із початковими значеннями.
    Bill();

    // Створює платіж за заданими даними.
    Bill(const string& surname,
        const string& phoneNumber,
        double tariff,
        double discount,
        const Time& startTime,
        const Time& endTime);

    // Створює копію іншого платежу.
    Bill(const Bill& other);

    // Ініціалізує поля платежу та обчислює суму.
    void Init(const string& surname,
        const string& phoneNumber,
        double tariff,
        double discount,
        const Time& startTime,
        const Time& endTime);

    // Вводить усі дані платежу з клавіатури.
    void Read();

    // Виводить інформацію про платіж на екран.
    void Display() const;

    // Повертає суму до оплати у вигляді рядка з гривнями.
    string toString() const;

    // Повертає прізвище платника.
    string GetSurname() const;

    // Повертає номер телефону.
    string GetPhoneNumber() const;

    // Повертає тариф за хвилину.
    double GetTariff() const;

    // Повертає знижку у відсотках.
    double GetDiscount() const;

    // Повертає час початку розмови.
    Time GetStartTime() const;

    // Повертає час закінчення розмови.
    Time GetEndTime() const;

    // Повертає суму до оплати.
    double GetAmount() const;

    // Змінює прізвище, якщо воно не порожнє.
    void SetSurname(const string& value);

    // Змінює номер телефону, якщо він коректний.
    void SetPhoneNumber(const string& value);

    // Змінює тариф і перераховує суму.
    void SetTariff(double value);

    // Змінює знижку та перераховує суму.
    void SetDiscount(double value);

    // Змінює час початку та перераховує суму.
    void SetStartTime(const Time& value);

    // Змінює час закінчення та перераховує суму.
    void SetEndTime(const Time& value);
};
