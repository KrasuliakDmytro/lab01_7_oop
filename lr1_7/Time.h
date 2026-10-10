#pragma once
#include <string>

using namespace std;

class Time
{
private:
    // Закриті поля для зберігання години, хвилини та секунди.
    unsigned int hour;
    unsigned int minute;
    unsigned int second;

    // Перевіряє, чи відповідають значення допустимому формату часу.
    bool IsValid(unsigned int h, unsigned int m, unsigned int s) const;

public:
    // Конструктор без параметрів. Створює час 00:00:00.
    Time();

    // Конструктор для створення часу за годиною, хвилиною та секундою.
    Time(unsigned int h, unsigned int m, unsigned int s);

    // Конструктор для створення часу з рядка, наприклад "12:30:45".
    Time(const string& str);

    // Конструктор для створення часу за кількістю секунд від початку доби.
    Time(unsigned int totalSeconds);

    // Конструктор копіювання іншого об'єкта Time.
    Time(const Time& other);

    // Ініціалізує поля часу з перевіркою правильності значень.
    void Init(unsigned int h, unsigned int m, unsigned int s);

    // Вводить час із клавіатури та перевіряє введені значення.
    void Read();

    // Виводить час на екран.
    void Display() const;

    // Повертає час у вигляді рядка формату "година:хвилина:секунда".
    string toString() const;

    // Повертає значення години.
    unsigned int GetHour() const;

    // Повертає значення хвилини.
    unsigned int GetMinute() const;

    // Повертає значення секунди.
    unsigned int GetSecond() const;

    // Змінює годину, якщо вона перебуває в межах від 0 до 23.
    void SetHour(unsigned int h);

    // Змінює хвилину, якщо вона перебуває в межах від 0 до 59.
    void SetMinute(unsigned int m);

    // Змінює секунду, якщо вона перебуває в межах від 0 до 59.
    void SetSecond(unsigned int s);

    // Переводить час у загальну кількість секунд від початку доби.
    unsigned int ToSeconds() const;

    // Переводить час у хвилини з округленням до найближчої цілої хвилини.
    unsigned int ToMinutes() const;

    // Обчислює різницю між двома моментами часу в секундах.
    int Difference(const Time& other) const;

    // Додає задану кількість секунд і повертає новий об'єкт часу.
    Time AddSeconds(int seconds) const;

    // Віднімає задану кількість секунд і повертає новий об'єкт часу.
    Time SubtractSeconds(int seconds) const;

    // Перевіряє, чи дорівнюють два моменти часу.
    bool operator==(const Time& other) const;

    // Перевіряє, чи не дорівнюють два моменти часу.
    bool operator!=(const Time& other) const;

    // Перевіряє, чи є поточний час ранішим за інший.
    bool operator<(const Time& other) const;

    // Перевіряє, чи є поточний час пізнішим за інший.
    bool operator>(const Time& other) const;

    // Перевіряє, чи поточний час раніший або дорівнює іншому.
    bool operator<=(const Time& other) const;

    // Перевіряє, чи поточний час пізніший або дорівнює іншому.
    bool operator>=(const Time& other) const;
};
