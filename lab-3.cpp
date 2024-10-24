#include <iostream>  
#include <cmath>       
#include <algorithm>   
#include <cstring>    

using namespace std;

double Function(double x, double a, double b, double c) {
    if (x < 0 && b != 0) {
        return a * x * x + b;
    }
    else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    }
    else {
        return x / c;
    }
}

int main(int argc, const char* argv[]) {
    setlocale(LC_ALL, "RUS");

    bool isHuman = true;

    if (argc > 1 && strcmp(argv[1], "false") == 0) {
        isHuman = false;
    }

    if (isHuman) {
        cout << "Введите 5 действительных чисел: " << endl;
    }

    double x1, x2, a, b, c;
    cin >> x1 >> x2 >> a >> b >> c;

    double step = (x2 - x1) / 14;
    double FirstArr[15], SecondArr[15];

    for (int i = 0, j = 14; i < 15; i++, j--) {
        double X = x1 + i * step;
        FirstArr[i] = Function(X, a, b, c);
        SecondArr[j] = Function(-X, a, b, c);

        int A = int(trunc(a)), B = int(trunc(b)), C = int(trunc(c));
        if (((A | B) & (A | C)) == 0) {
            FirstArr[i] = trunc(FirstArr[i]);
            SecondArr[j] = trunc(SecondArr[j]);
        }
        else {
            FirstArr[i] = round(FirstArr[i] * 100) / 100;
            SecondArr[j] = round(SecondArr[j] * 100) / 100;
        }
    }

    double mn_1 = min({ FirstArr[0], FirstArr[1], FirstArr[2], FirstArr[3], FirstArr[4] });
    double mn_2 = min({ FirstArr[5], FirstArr[6], FirstArr[7], FirstArr[8], FirstArr[9] });
    double mn_3 = min({ FirstArr[10], FirstArr[11], FirstArr[12], FirstArr[13], FirstArr[14] });

    double SortArr[15];
    copy(begin(FirstArr), end(FirstArr), begin(SortArr));
    sort(begin(SortArr), end(SortArr));

    int Replay = 0;
    for (int i = 1; i < 15; i++) {
        if (SortArr[i] == SortArr[i - 1]) {
            Replay++;
        }
    }

    int two = -1;
    for (int i = 0; i < 15; i++) {
        bool isPowerOfTwo = true;
        int expectedPower = 1;
        for (int j = i; j < 15; j++) {
            if (FirstArr[j] != expectedPower) {
                isPowerOfTwo = false;
                break;
            }
            expectedPower *= 2;
        }
        if (isPowerOfTwo) {
            two = i;
            break;
        }
    }

    double NewFirstArr[15] = { 0 };
    double NewSecondArr[15] = { 0 };

    // перераспределение элементов
    int firstIndex = 0, secondIndex = 0;

    // заполняем отрицательные числа в первый массив
    for (int i = 0; i < 15; i++) {
        if (FirstArr[i] < 0) {
            NewFirstArr[firstIndex++] = FirstArr[i];
        }
    }
    for (int i = 0; i < 15; i++) {
        if (SecondArr[i] < 0) {
            NewFirstArr[firstIndex++] = SecondArr[i];
        }
    }

    // заполняем положительные числа во второй массив
    for (int i = 0; i < 15; i++) {
        if (SecondArr[i] > 0) {
            NewSecondArr[secondIndex++] = SecondArr[i];
        }
    }
    for (int i = 0; i < 15; i++) {
        if (FirstArr[i] > 0) {
            NewSecondArr[secondIndex++] = FirstArr[i];
        }
    }

    // вывод результатов
    if (isHuman) {
        cout << "Первый массив: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << FirstArr[i] << " ";
            }
            else {
                cout << FirstArr[i];
            }
        }
        cout << endl;

        cout << "Второй массив: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << SecondArr[i] << " ";
            }
            else {
                cout << SecondArr[i];
            }
        }
        cout << endl;

        cout << mn_1 << endl;
        cout << mn_2 << endl;
        cout << mn_3 << endl;

        cout << "Сортировка: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << SortArr[i] << " ";
            }
            else {
                cout << SortArr[i];
            }
        }
        cout << endl;

        cout << "Повторы: " << Replay << endl;

        cout << "Степень 2: " << two << endl;

        cout << "Перераспределение 1 массива: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << NewFirstArr[i] << " ";
            }
            else {
                cout << NewFirstArr[i];
            }
        }
        cout << endl;

        cout << "Перераспределение 2 массива: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << NewSecondArr[i] << " ";
            }
            else {
                cout << NewSecondArr[i];
            }
        }
        cout << endl;
    }
    else {
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << FirstArr[i] << " ";
            }
            else {
                cout << FirstArr[i];
            }
        }
        cout << endl;

        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << SecondArr[i] << " ";
            }
            else {
                cout << SecondArr[i];
            }
        }
        cout << endl;

        cout << mn_1 << endl;
        cout << mn_2 << endl;
        cout << mn_3 << endl;

        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << SortArr[i] << " ";
            }
            else {
                cout << SortArr[i];
            }
        }
        cout << endl;

        cout << Replay << endl;

        cout << two << endl;

        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << NewFirstArr[i] << " ";
            }
            else {
                cout << NewFirstArr[i];
            }
        }
        cout << endl;

        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << NewSecondArr[i] << " ";
            }
            else {
                cout << NewSecondArr[i];
            }
        }
        cout << endl;
    }

    return 0;
}
