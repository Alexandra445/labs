#include <iostream>
#include <cmath>
#include <cstring>  
#include <iomanip>

using namespace std;

constexpr size_t capacity = 15;
const double EPSILON = 1e-6;

static double Function(double x, double a, double b, double c) {
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

static void PrintArray(const double* array_ptr, const size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (i == length - 1) {
            std::cout << array_ptr[i] << std::endl;
        }
        else {
            std::cout << array_ptr[i] << " ";
        }
    }
} 

static double* SelectSort(double from[]) {
    double* to = new double[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        to[i] = from[i];
    } 
    for (size_t i = 0; i < capacity - 1; ++i) {
        for (size_t j = i + 1; j < capacity; ++j) {
            if (to[i] > to[j]) {
                std::swap(to[i], to[j]);
            }
        }
    }
    return to;
}

static void FreeArray(double* arr_) {
    if (arr_ != nullptr) {
        delete[] arr_;
    }
}

static size_t ComputeReplays(double arr_[]) {
    double* sortedArr = SelectSort(arr_);
    size_t replay = 0;
    size_t i = 0;

    while (i < capacity) { 
        size_t count = 0;
        while ((i + count < capacity) && (sortedArr[i] == sortedArr[i + count])) {
            count++;
        }
        if (count > 1) {
            replay++;
        }
        i += count; 
    }

    delete[] sortedArr; 
    return replay;
}

template <typename T>
static bool IsPowerOfTwo(T num) {
    if (num <= 0.) {
        return false;
    }
    double log2num = std::log2(num);
    return std::fabs(log2num - std::round(log2num)) < 1e-9;
}

static int ComputeTwo(const double arr_[]) {
    for (size_t i = 0; i < capacity; ++i) {
        if (IsPowerOfTwo(arr_[i])) {
            size_t j = i + 1;
            double last_num = arr_[i];
            while (j < capacity && IsPowerOfTwo(arr_[j]) && arr_[j] > last_num) {
                last_num = arr_[j];
                ++j;
            }

            if (j == capacity) {
                return i; 
            }
        }
    }
    return -1;  
}

static void PrintTable(const double* arr, double x_start, double step, bool reverse = false) {
    cout << "_______________________________" << endl;
    cout << "|     x     |       F(x)      |" << endl;
    cout << "|___________|_________________|" << endl;

    for (size_t i = 0; i < capacity; ++i) {
        double x = x_start + i * step;
        if (reverse) x = -x;
        cout << "|" << std::setw(10) << right << x << " | "
            << setw(15) << fixed << std::setprecision(2) << arr[i] << " |" << endl;
    }

    cout << "|___________|_________________|" << endl;
}

static void ReplaceZeros(double* arr_) {
    for (size_t i = 0; i < capacity; ++i) {
        if (arr_[i] == 0.0 && signbit(arr_[i])) {
            arr_[i] = 0.0;
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
    double FirstArr[capacity] = { 0.0 };
    double SecondArr[capacity] = { 0.0 };

    for (int i = 0, j = capacity - 1; i < capacity; i++, j--) {
        double X = x1 + i * step;
        FirstArr[i] = Function(X, a, b, c);
        SecondArr[j] = Function(-X, a, b, c);

        int A = int(trunc(a)), B = int(trunc(b)), C = int(trunc(c));

        // Проверка условия для округления
        if (((A | B) & (A | C)) == 0) {
            // Округление до целого числа
            FirstArr[i] = round(FirstArr[i]);
            SecondArr[j] = round(SecondArr[j]);
        }
        else {
            // Округление до двух знаков после запятой
            FirstArr[i] = round(FirstArr[i] * 100.0) / 100.0;
            SecondArr[j] = round(SecondArr[j] * 100.0) / 100.0;
        }
    }

    double mn_1 = min({ FirstArr[0], FirstArr[1], FirstArr[2], FirstArr[3], FirstArr[4] });
    double mn_2 = min({ FirstArr[5], FirstArr[6], FirstArr[7], FirstArr[8], FirstArr[9] });
    double mn_3 = min({ FirstArr[10], FirstArr[11], FirstArr[12], FirstArr[13], FirstArr[14] });

    double* SortArr = SelectSort(FirstArr); 
    size_t Replay = ComputeReplays(FirstArr); 
    int two = ComputeTwo(FirstArr);

    // Замена -0.0 на 0.0
    ReplaceZeros(FirstArr);
    ReplaceZeros(SecondArr);
    ReplaceZeros(SortArr); 

    double NewFirstArr[capacity] = { 0.0 };
    double NewSecondArr[capacity] = { 0.0 };

    size_t firstIndex = 0, secondIndex = 0;
    for (size_t i = 0; i < capacity; i++) {
        if (FirstArr[i] < -EPSILON && firstIndex < capacity) {
            NewFirstArr[firstIndex++] = FirstArr[i];
        }
    }
    for (size_t i = 0; i < capacity; i++) {
        if (SecondArr[i] < -EPSILON && firstIndex < capacity) {
            NewFirstArr[firstIndex++] = SecondArr[i];
        }
    }
    for (size_t i = 0; i < capacity; i++) {
        if (SecondArr[i] >= EPSILON && secondIndex < capacity) {
            NewSecondArr[secondIndex++] = SecondArr[i];
        }
    }
    for (size_t i = 0; i < capacity; i++) {
        if (FirstArr[i] >= EPSILON && secondIndex < capacity) {
            NewSecondArr[secondIndex++] = FirstArr[i];
        }
    }

    if (isHuman) {
        cout << "Первый массив: " << std::endl; 
        PrintTable(FirstArr, x1, step);

        cout << "Второй массив: " << std::endl; 
        PrintTable(SecondArr, x1, step, true);

        std::cout << "Минимумы: " << std::endl;
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

    FreeArray(SortArr);

    return 0;
} 
