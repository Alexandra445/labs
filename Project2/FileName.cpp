#include<iostream> 
#include<cmath> 
#include<iomanip> 
#include <cstring>

using namespace std;

int n, x, f, mx, mn, k1, k2, k3, p1, p2, p3;
double sum, y;

int main(int argc, const char* argv[])
{
    setlocale(LC_ALL, "RUS");

    bool isHuman = true;

    if (argc > 1 && strcmp(argv[1], "false") == 0) {
        isHuman = false;
    }

    if (isHuman) {
        cout << "Введите количество чисел в последовательности: " << endl;
    }
    cin >> n;
    mn = 1000000;

    if (isHuman) {
        cout << "Введите последовательность положительных целых чисел: " << endl;
    }

    for (int i = 0; i < n; i++) {
        cin >> x;

        // Находим простые числа последовательности 
        f = 0;
        if (x != 1) {
            for (int j = 2; j <= sqrt(x); j++) {
                if (x % j == 0) {
                    f = 1;
                }
            }
            if (f == 0) {
                cout << x << " является простым числом." << endl;
            }
        }

        // Находим сумму всех элементов последовательности 
        sum += x;
        // Находим min и max в последовательности 
        mn = min(mn, x);
        mx = max(mx, x);
        // Находим количество чисел кратных 5 
        if (x % 5 == 0) {
            k1++;
        }
        // Находим количество чисел являющихся степенью двойки 
        y = x;
        while (y > 1) {
            y /= 2;
        }
        if (y == 1) {
            k2++;
        }
        // Находим количество чисел, превышающих сумму двух предшествующих членов последовательности 
        p1 = p2;
        p2 = p3;
        p3 = x;
        if (i >= 2) {
            if (p3 > p1 + p2) {
                k3++;
            }
        }
    }

    cout << "Среднее арифметическое введеных чисел: " << fixed << setprecision(2) << (sum) / n << endl;
    cout << "Разница между максимумом и минимумом: " << mx - mn << endl;
    cout << "Количество чисел, кратных числу 5: " << k1 << endl;
    cout << "Количество чисел, являющихся степенью двойки: " << k2 << endl;
    cout << "Количество чисел, превышающих сумму двух предшествующих членов последовательности: " << k3 << endl;

    return 0;
}