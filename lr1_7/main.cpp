#include <iostream>
#include <windows.h>
#include "Time.h"
#include "Bill.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "========== КЛАС TIME ==========\n\n";

    // 1. Створення конструктором без параметрів
    Time t1;
    cout << "t1 = ";
    t1.Display();
    cout << endl;

    // 2. Створення числами
    Time t2(12, 30, 45);
    cout << "t2 = ";
    t2.Display();
    cout << endl;

    // 3. Створення літерним рядком
    Time t3("23:59:59");
    cout << "t3 = ";
    t3.Display();
    cout << endl;

    // 4. Створення кількістю секунд
    Time t4(3661);
    cout << "t4 = ";
    t4.Display();
    cout << endl;

    // 5. Створення копіюванням
    Time t5(t2);
    cout << "t5 = ";
    t5.Display();
    cout << endl;

    cout << "\nСекунди t2: " << t2.ToSeconds() << endl;
    cout << "Хвилини t2: " << t2.ToMinutes() << endl;

    cout << "\nРізниця t2 і t4: "
        << t2.Difference(t4) << " секунд\n";

    Time t6 = t2.AddSeconds(100);
    cout << "t2 + 100 секунд = ";
    t6.Display();
    cout << endl;

    Time t7 = t2.SubtractSeconds(100);
    cout << "t2 - 100 секунд = ";
    t7.Display();
    cout << endl;

    cout << "\nПорівняння:\n";

    if (t2 > t4)
        cout << "t2 > t4\n";
    else
        cout << "t2 <= t4\n";


    cout << "\n========== КЛАС BILL ==========\n\n";

    // Створення об'єкта без параметрів
    Bill bill1;

    // Введення через Read()
    cout << "Введіть дані першого платежу:\n\n";
    bill1.Read();

    cout << "\nІнформація про перший платіж:\n";
    bill1.Display();


    // Створення через конструктор
    Time start2(10, 20, 30);
    Time end2(11, 25, 45);

    Bill bill2(
        "Петренко",
        "+380501234567",
        5.50,
        10,
        start2,
        end2
    );

    cout << "\nДругий платіж:\n";
    bill2.Display();


    // Створення копіюванням
    Bill bill3(bill2);

    cout << "\nТретій платіж (копія другого):\n";
    bill3.Display();


    // Динамічний масив об'єктів
    int n = 2;

    Bill* bills = new Bill[n];

    bills[0] = bill1;
    bills[1] = bill2;

    cout << "\n========== МАСИВ BILL ==========\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nПлатіж №" << i + 1 << ":\n";
        bills[i].Display();
    }

    delete[] bills;


    // Масив Time
    Time times[3] =
    {
        Time(8, 15, 0),
        Time("12:30:45"),
        Time(18, 45, 30)
    };

    cout << "\n========== МАСИВ TIME ==========\n";

    for (int i = 0; i < 3; i++)
    {
        cout << "Час №" << i + 1 << ": ";
        times[i].Display();
        cout << endl;
    }


    // Демонстрація методів доступу
    cout << "\n========== GET / SET ==========\n";

    cout << "Прізвище bill2: "
        << bill2.GetSurname() << endl;

    bill2.SetSurname("Іваненко");

    cout << "Нове прізвище: "
        << bill2.GetSurname() << endl;

    cout << "Тариф: "
        << bill2.GetTariff() << endl;

    bill2.SetTariff(6.00);

    cout << "Новий тариф: "
        << bill2.GetTariff() << endl;

    cout << "\nОновлений платіж:\n";
    bill2.Display();

    return 0;
}