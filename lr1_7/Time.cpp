#include "Time.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Перевіряє, чи є година, хвилина та секунда коректними.
bool Time::IsValid(unsigned int h, unsigned int m, unsigned int s) const
{
    return h < 24 && m < 60 && s < 60;
}

// Створює об'єкт із початковим часом 00:00:00.
Time::Time()
{
    hour = 0;
    minute = 0;
    second = 0;
}

// Створює час за трьома числовими значеннями.
Time::Time(unsigned int h, unsigned int m, unsigned int s)
{
    Init(h, m, s);
}

// Створює час із рядка формату "година:хвилина:секунда".
// Якщо рядок неправильний, встановлюється час 00:00:00.
Time::Time(const string& str)
{
    unsigned int h, m, s;
    char c1, c2;
    stringstream ss(str);
    char extra;

    if (ss >> h >> c1 >> m >> c2 >> s &&
        !(ss >> extra) &&
        c1 == ':' && c2 == ':' &&
        IsValid(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

// Створює час за кількістю секунд від початку доби.
// Якщо секунд більше ніж у добі, зайві секунди відкидаються.
Time::Time(unsigned int totalSeconds)
{
    totalSeconds %= 86400;

    hour = totalSeconds / 3600;
    minute = (totalSeconds % 3600) / 60;
    second = totalSeconds % 60;
}

// Створює копію іншого об'єкта Time.
Time::Time(const Time& other)
{
    hour = other.hour;
    minute = other.minute;
    second = other.second;
}

// Записує нові значення часу.
// Якщо хоча б одне значення неправильне, встановлює 00:00:00.
void Time::Init(unsigned int h, unsigned int m, unsigned int s)
{
    if (IsValid(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

// Зчитує час із клавіатури та повторює введення,
// доки користувач не введе правильні значення.
void Time::Read()
{
    unsigned int h, m, s;

    while (true)
    {
        cout << "Введіть годину (0-23): ";
        if (!(cin >> h))
        {
            cin.clear();
            cin.get();
            cout << "Помилка введення!\n";
            continue;
        }

        cout << "Введіть хвилину (0-59): ";
        if (!(cin >> m))
        {
            cin.clear();
            cin.get();
            cout << "Помилка введення!\n";
            continue;
        }

        cout << "Введіть секунду (0-59): ";
        if (!(cin >> s))
        {
            cin.clear();
            cin.get();
            cout << "Помилка введення!\n";
            continue;
        }

        // Перевіряє всі три значення перед записом.
        if (IsValid(h, m, s))
        {
            Init(h, m, s);
            break;
        }

        cout << "Некоректний час! Спробуйте ще раз.\n";
    }
}

// Виводить час на екран у форматі "година:хвилина:секунда".
void Time::Display() const
{
    cout << toString();
}

// Перетворює час на рядок із двозначними годинами, хвилинами та секундами.
string Time::toString() const
{
    stringstream ss;

    ss << setfill('0')
        << setw(2) << hour << ":"
        << setw(2) << minute << ":"
        << setw(2) << second;

    return ss.str();
}

// Повертає годину.
unsigned int Time::GetHour() const
{
    return hour;
}

// Повертає хвилину.
unsigned int Time::GetMinute() const
{
    return minute;
}

// Повертає секунду.
unsigned int Time::GetSecond() const
{
    return second;
}

// Змінює годину, якщо вона не перевищує 23.
void Time::SetHour(unsigned int h)
{
    if (h < 24)
        hour = h;
}

// Змінює хвилину, якщо вона не перевищує 59.
void Time::SetMinute(unsigned int m)
{
    if (m < 60)
        minute = m;
}

// Змінює секунду, якщо вона не перевищує 59.
void Time::SetSecond(unsigned int s)
{
    if (s < 60)
        second = s;
}

// Обчислює кількість секунд від початку доби.
unsigned int Time::ToSeconds() const
{
    return hour * 3600 + minute * 60 + second;
}

// Переводить час у хвилини з округленням до найближчої цілої хвилини.
unsigned int Time::ToMinutes() const
{
    return static_cast<unsigned int>(round(ToSeconds() / 60.0));
}

// Обчислює різницю між поточним часом та іншим часом у секундах.
// Результат може бути від'ємним.
int Time::Difference(const Time& other) const
{
    return static_cast<int>(ToSeconds()) -
        static_cast<int>(other.ToSeconds());
}

// Додає задану кількість секунд до часу.
// Після завершення доби час переходить на початок наступної доби.
Time Time::AddSeconds(int seconds) const
{
    long long result = static_cast<long long>(ToSeconds()) + seconds;

    result = ((result % 86400) + 86400) % 86400;

    return Time(static_cast<unsigned int>(result));
}

// Віднімає задану кількість секунд за допомогою додавання
// від'ємної кількості секунд.
Time Time::SubtractSeconds(int seconds) const
{
    return AddSeconds(-seconds);
}

// Перевіряє рівність двох моментів часу.
bool Time::operator==(const Time& other) const
{
    return ToSeconds() == other.ToSeconds();
}

// Перевіряє нерівність двох моментів часу.
bool Time::operator!=(const Time& other) const
{
    return !(*this == other);
}

// Перевіряє, чи є поточний час ранішим за інший.
bool Time::operator<(const Time& other) const
{
    return ToSeconds() < other.ToSeconds();
}

// Перевіряє, чи є поточний час пізнішим за інший.
bool Time::operator>(const Time& other) const
{
    return ToSeconds() > other.ToSeconds();
}

// Перевіряє, чи поточний час раніший або дорівнює іншому.
bool Time::operator<=(const Time& other) const
{
    return ToSeconds() <= other.ToSeconds();
}

// Перевіряє, чи поточний час пізніший або дорівнює іншому.
bool Time::operator>=(const Time& other) const
{
    return ToSeconds() >= other.ToSeconds();
}
