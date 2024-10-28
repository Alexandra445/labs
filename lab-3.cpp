#include <iostream>  
#include <cmath>     

using namespace std;

constexpr size_t capacity = 15;

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

void PrintArray(const double* array_ptr, const size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (i == length - 1) {
            std::cout << array_ptr[i] << std::endl;
        }
        else {
            std::cout << array_ptr[i] << " ";
        }
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

    double step = (x2 - x1) / (capacity - 1);
    double FirstArr[capacity] = { 0 };
    double SecondArr[capacity] = { 0 };

    for (int i = 0, j = capacity - 1; i < capacity; i++, j--) {
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

    double SortArr[capacity] = { 0 };
    for (size_t i = 0; i < capacity; ++i) {
        SortArr[i] = FirstArr[i];
    }

    // Сортировка выбором
    for (size_t i = 0; i < capacity - 1; ++i) {

        for (size_t j = i + 1; j < capacity; ++j) {
            if (SortArr[j] == -0.0) {
                SortArr[j] = 0.0;
            }
            if (SortArr[i] > SortArr[j]) {
                std::swap(SortArr[i], SortArr[j]);
            }
        }
    }

    size_t Replay = 0;
    bool counted[capacity] = { false };

    for (int i = 0; i < capacity; i++) {
        if (counted[i]) {
            continue;
        }

        size_t count = 1; 
        for (int j = i + 1; j < capacity; j++) {
            if (FirstArr[i] == FirstArr[j]) {
                count++; 
                counted[j] = true; 
            }
        }

        if (count > 1) {
            Replay++;
        }
    }

    int two = -1;
    for (size_t i = 0; i < capacity; ++i) {
        bool isPowerOfTwo = true;
        int expectedPower = 1;
        for (size_t j = i; j < capacity; ++j) {
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

    for (size_t i = 0; i < capacity; ++i) {
        if (FirstArr[i] == -0.0) {
            FirstArr[i] = 0.0;
        }
        if (SecondArr[i] == -0.0) {
            SecondArr[i] = 0.0;
        }
        if (SortArr[i] == -0.0) {
            SortArr[i] = 0.0;
        }
    }

    double NewFirstArr[capacity] = { 0 };
    double NewSecondArr[capacity] = { 0 };

    // перераспределение элементов 
    int firstIndex = 0, secondIndex = 0;
    for (size_t i = 0; i < capacity; i++) {
        if (FirstArr[i] < 0 && firstIndex < capacity) {
            NewFirstArr[firstIndex++] = FirstArr[i];
        }
    }
    for (size_t i = 0; i < capacity; i++) {
        if (SecondArr[i] < 0 && firstIndex < capacity) {
            NewFirstArr[firstIndex++] = SecondArr[i];
        }
    }
    
    for (size_t i = 0; i < capacity; i++) {
        if (SecondArr[i] > 0 && secondIndex < capacity) {
            NewSecondArr[secondIndex++] = SecondArr[i];
        }
    }
    for (size_t i = 0; i < capacity; i++) {
        if (FirstArr[i] > 0 && secondIndex < capacity) {
            NewSecondArr[secondIndex++] = FirstArr[i];
        }
    }

    if (isHuman) {
        cout << "Первый массив: ";
        PrintArray(FirstArr, capacity);

        cout << "Второй массив: ";
        PrintArray(SecondArr, capacity);

        cout << mn_1 << endl;
        cout << mn_2 << endl;
        cout << mn_3 << endl;

        cout << "Сортировка: ";
        PrintArray(SortArr, capacity);

        cout << "Повторы: " << Replay << endl;
        cout << "Степень 2: " << two << endl;

        cout << "Перераспределение 1 массива: ";
        PrintArray(NewFirstArr, capacity);

        cout << "Перераспределение 2 массива: ";
        PrintArray(NewSecondArr, capacity);
    }
    else {
        PrintArray(FirstArr, capacity);
        PrintArray(SecondArr, capacity);

        cout << mn_1 << endl;
        cout << mn_2 << endl;
        cout << mn_3 << endl;

        PrintArray(SortArr, capacity);

        cout << Replay << endl;
        cout << two << endl;

        PrintArray(NewFirstArr, capacity);
        PrintArray(NewSecondArr, capacity);
    }

    return 0;
}
