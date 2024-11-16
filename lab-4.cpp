#include <iostream>  
#include <cmath>  
#include <cstring> 

using namespace std;

template <typename T>
void PrintMatrix(T** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cout << matrix[i][j] << (j == cols - 1 ? "" : " ");
        }
        cout << endl;
    }
}

template <typename T>
T** AllocateMatrix(size_t rows, size_t cols, bool initialize = true, T initialValue = T()) {
    T** matrix = new T * [rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new T[cols];
        if (initialize) {
            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = initialValue;
            }
        }
    }
    return matrix;
}
 
template <typename T>
void FreeMatrix(T** matrix, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template <typename T>
T** GetMatrix(size_t rows, size_t cols, bool isHuman) {
    T** matrix = AllocateMatrix<T>(rows, cols);
    if (isHuman) {
        cout << "Введите элементы матрицы построчно:" << endl;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

template <typename T, typename U>
T** MultiplyMatrices(T** a, U** b, size_t aRows, size_t aCols, size_t bCols) {
    T** result = AllocateMatrix<T>(aRows, bCols, true, 0);
    for (size_t i = 0; i < aRows; ++i) {
        for (size_t j = 0; j < bCols; ++j) {
            for (size_t k = 0; k < aCols; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}
 
template <typename T>
T** MatrixPower(T** matrix, int exponent, size_t size) {
    if (exponent < 0) {
        throw runtime_error("Показатель степени должен быть неотрицательным.");
    }
    if (exponent == 0) {
        return AllocateMatrix<T>(size, size, true, (T)(size == 0 ? 0 : (size_t)(size_t)1));
    }
    if (exponent == 1) {

        T** result = AllocateMatrix<T>(size, size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result[i][j] = matrix[i][j];
            }
        }
        return result;
    }

    T** result = MatrixPower(matrix, exponent / 2, size);
    T** temp = MultiplyMatrices(result, result, size, size, size);
    FreeMatrix(result, size);
    if (exponent % 2 != 0) {
        T** temp2 = MultiplyMatrices(temp, matrix, size, size, size);
        FreeMatrix(temp, size);
        return temp2;
    }
    else {
        return temp;
    }
}

int main(int argc, const char* argv[]) {
    setlocale(LC_ALL, "RUS");
    bool isHuman = (argc <= 1 || strcmp(argv[1], "false") != 0);

    size_t n, m, k;

    if (isHuman) {
        cout << "Введите количество строк (N): ";
    }
    cin >> n;

    if (isHuman) {
        cout << "Введите количество столбцов (M): ";
    }
    cin >> m;

    int64_t** a1 = GetMatrix<int64_t>(n, m, isHuman);

    int choice;
    while (true) {
        if (isHuman) {
            cout << "Введите команду (0 - выход, 1 - вывести A1, 2 - умножить A1 на A2, 3 - возвести A1 в степень): ";
        }
        cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) {
            PrintMatrix(a1, n, m);
        }
        else if (choice == 2) {
            if (isHuman) {
                cout << "Введите количество столбцов для A2 (K): ";
            }
            cin >> k;
            int64_t** a2 = GetMatrix<int64_t>(m, k, isHuman);
            int64_t** result = MultiplyMatrices(a1, a2, n, m, k);
            FreeMatrix(a1, n);
            a1 = result;
            m = k;
            FreeMatrix(a2, m);
        }
        else if (choice == 3) {
            if (n != m) {
                cout << "NO" << endl;
            }
            else {
                int x;
                if (isHuman) {
                    cout << "Введите показатель степени (x): ";
                }
                cin >> x;
                try {
                    int64_t** result = MatrixPower(a1, x, n);
                    FreeMatrix(a1, n);
                    a1 = result;
                }
                catch (const runtime_error& error) {
                    cerr << "Ошибка: " << error.what() << endl;
                }
            }
        }
    }
    FreeMatrix(a1, n);
    return 0;
}
