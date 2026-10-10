#include "Bill.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cmath>
#include <limits>

using namespace std;

// Перевіряє, чи є тариф невід'ємним скінченним числом.
bool Bill::IsValidTariff(double value) const
{
    return isfinite(value) && value >= 0;
}

// Перевіряє, чи перебуває знижка в межах від 0 до 100%.
bool Bill::IsValidDiscount(double value) const
{
    return isfinite(value) && value >= 0 && value <= 100;
}

// Перевіряє номер телефону.
// Дозволяє цифри, знак плюс, дефіс, дужки та пробіли.
bool Bill::IsValidPhone(const string& value) const
{
    if (value.empty())
        return false;

    bool hasDigit = false;

    for (char c : value)
    {
        if (isdigit(static_cast<unsigned char>(c)))
        {
            hasDigit = true;
        }
        else if (c != '+' && c != '-' &&
            c != '(' && c != ')' && c != ' ')
        {
            return false;
        }
    }

    return hasDigit;
}

// Обчислює тривалість розмови в секундах.
// Якщо розмова закінчується після півночі, враховує перехід доби.
// Неповна хвилина округлюється вгору.
// Після цього застосовується знижка.
void Bill::CalculateAmount()
{
    long long seconds =
        static_cast<long long>(endTime.ToSeconds()) -
        static_cast<long long>(startTime.ToSeconds());

    // Якщо кінець розмови раніше за початок, розмова перейшла через північ.
    if (seconds < 0)
        seconds += 86400;

    // Перетворює секунди в хвилини з округленням угору.
    long long minutes = (seconds + 59) / 60;

    // Обчислює суму з урахуванням тарифу та знижки.
    amount = minutes * tariff * (1.0 - discount / 100.0);
}

// Створює платіж із початковими значеннями всіх полів.
Bill::Bill()
{
    surname = "";
    phoneNumber = "";
    tariff = 0;
    discount = 0;
    startTime = Time();
    endTime = Time();
    amount = 0;
}

// Створює платіж за заданими параметрами.
// Спочатку встановлює безпечні початкові значення,
// після чого викликає метод Init().
Bill::Bill(const string& surname,
    const string& phoneNumber,
    double tariff,
    double discount,
    const Time& startTime,
    const Time& endTime)
{
    this->surname = "";
    this->phoneNumber = "";
    this->tariff = 0;
    this->discount = 0;
    this->startTime = Time();
    this->endTime = Time();
    this->amount = 0;

    Init(surname, phoneNumber, tariff, discount, startTime, endTime);
}

// Створює копію іншого об'єкта Bill.
Bill::Bill(const Bill& other)
{
    surname = other.surname;
    phoneNumber = other.phoneNumber;
    tariff = other.tariff;
    discount = other.discount;
    startTime = other.startTime;
    endTime = other.endTime;
    amount = other.amount;
}

// Записує дані платежу через методи перевірки.
// Наприкінці перераховує суму до оплати.
void Bill::Init(const string& surname,
    const string& phoneNumber,
    double tariff,
    double discount,
    const Time& startTime,
    const Time& endTime)
{
    SetSurname(surname);
    SetPhoneNumber(phoneNumber);
    SetTariff(tariff);
    SetDiscount(discount);
    SetStartTime(startTime);
    SetEndTime(endTime);

    CalculateAmount();
}

// Вводить дані платежу з клавіатури.
// Повторює введення, якщо дані не відповідають вимогам.
void Bill::Read()
{
    string value;
    double number;

    // Введення прізвища.
    do
    {
        cout << "Введіть прізвище платника: ";
        cin >> value;

        if (value.empty())
            cout << "Прізвище не може бути порожнім!\n";

    } while (value.empty());

    SetSurname(value);

    // Введення номера телефону.
    do
    {
        cout << "Введіть номер телефону: ";
        cin >> value;

        if (!IsValidPhone(value))
            cout << "Некоректний номер телефону!\n";

    } while (!IsValidPhone(value));

    SetPhoneNumber(value);

    // Введення тарифу.
    do
    {
        cout << "Введіть тариф за хвилину (грн): ";

        if (!(cin >> number))
        {
            cin.clear();
            cin.get();
            cout << "Потрібно ввести число!\n";
            continue;
        }

        if (!IsValidTariff(number))
            cout << "Тариф повинен бути невід'ємним!\n";

    } while (!IsValidTariff(number));

    SetTariff(number);

    // Введення знижки.
    do
    {
        cout << "Введіть знижку (0-100%): ";

        if (!(cin >> number))
        {
            cin.clear();
            cin.get();
            cout << "Потрібно ввести число!\n";
            continue;
        }

        if (!IsValidDiscount(number))
            cout << "Знижка має бути від 0 до 100%!\n";

    } while (!IsValidDiscount(number));

    SetDiscount(number);

    // Введення часу початку розмови.
    cout << "\nЧас початку розмови:\n";
    startTime.Read();

    // Введення часу закінчення розмови.
    cout << "\nЧас закінчення розмови:\n";
    endTime.Read();

    // Перераховує суму після введення всіх даних.
    CalculateAmount();
}

// Виводить усі дані про платіж.
// Суму в гривнях отримує через метод toString().
void Bill::Display() const
{
    cout << fixed << setprecision(2);

    cout << "Прізвище платника: " << surname << endl;
    cout << "Номер телефону: " << phoneNumber << endl;
    cout << "Тариф за хвилину: " << tariff << " грн" << endl;
    cout << "Знижка: " << discount << "%" << endl;
    cout << "Початок розмови: " << startTime.toString() << endl;
    cout << "Кінець розмови: " << endTime.toString() << endl;
    cout << "Сума до оплати: " << toString() << endl;
}

// Перетворює суму платежу на рядок із двома знаками після коми.
string Bill::toString() const
{
    stringstream ss;

    ss << fixed << setprecision(2) << amount << " грн";

    return ss.str();
}

// Повертає прізвище платника.
string Bill::GetSurname() const
{
    return surname;
}

// Повертає номер телефону.
string Bill::GetPhoneNumber() const
{
    return phoneNumber;
}

// Повертає тариф за хвилину.
double Bill::GetTariff() const
{
    return tariff;
}

// Повертає знижку у відсотках.
double Bill::GetDiscount() const
{
    return discount;
}

// Повертає час початку розмови.
Time Bill::GetStartTime() const
{
    return startTime;
}

// Повертає час закінчення розмови.
Time Bill::GetEndTime() const
{
    return endTime;
}

// Повертає розраховану суму платежу.
double Bill::GetAmount() const
{
    return amount;
}

// Змінює прізвище, якщо нове значення не порожнє.
void Bill::SetSurname(const string& value)
{
    if (!value.empty())
        surname = value;
}

// Змінює номер телефону, якщо він пройшов перевірку.
void Bill::SetPhoneNumber(const string& value)
{
    if (IsValidPhone(value))
        phoneNumber = value;
}

// Змінює тариф і перераховує суму.
void Bill::SetTariff(double value)
{
    if (IsValidTariff(value))
    {
        tariff = value;
        CalculateAmount();
    }
}

// Змінює знижку та перераховує суму.
void Bill::SetDiscount(double value)
{
    if (IsValidDiscount(value))
    {
        discount = value;
        CalculateAmount();
    }
}

// Змінює час початку розмови та перераховує суму.
void Bill::SetStartTime(const Time& value)
{
    startTime = value;
    CalculateAmount();
}

// Змінює час закінчення розмови та перераховує суму.
void Bill::SetEndTime(const Time& value)
{
    endTime = value;
    CalculateAmount();
}
