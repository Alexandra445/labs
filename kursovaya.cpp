#include <iostream>
#include <fstream>
#include <unordered_map>
#define NOMINMAX
#include <Windows.h>

// Функция для динамического создания квадратной матрицы
int** createMatrix(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size] {0}; // Инициализация нулями
    }
    return matrix;
}

// Функция для удаления матрицы
void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция для ввода матрицы с консоли
void inputMatrix(int** matrix, int size) {
    std::cout << "Введите элементы матрицы размером " << size << "x" << size << ":\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

// Функция для вывода матрицы на консоль
void outputMatrix(int** matrix, int size) {
    std::cout << "Матрица:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для записи матрицы в файл
void saveMatrixToFile(const std::string& filename, int** matrix, int size) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << matrix[i][j] << " ";
            }
            file << "\n";
        }
        file.close();
        std::cout << "Матрица успешно сохранена в файл " << filename << ".\n";
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << " для записи.\n";
    }
}

// Функция для загрузки матрицы из файла
void loadMatrixFromFile(const std::string& filename, int** matrix, int size) {
    std::ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> matrix[i][j];
            }
        }
        file.close();
        std::cout << "Матрица успешно загружена из файла " << filename << ".\n";
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << " для чтения.\n";
    }
}

// Функция для редактирования элемента матрицы
void editMatrixElement(int** matrix) {
    int x, y, newValue;
    std::cout << "Введите координаты элемента (x, y), который хотите изменить: ";
    std::cin >> x >> y;
    std::cout << "Введите новое значение элемента: ";
    std::cin >> newValue;
    if (x >= 0 && y >= 0) {
        matrix[x][y] = newValue;
    }
    else {
        std::cerr << "Неверные координаты элемента.\n";
    }
}

// Функция для копирования элементов из матрицы A в C, которые более одного раза встречаются в B
void copyRepeatedElements(int** A, int** B, int** C, int size) {
    std::unordered_map<int, int> frequencyMap;

    // Подсчитать частоту элементов в матрице B
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            frequencyMap[B[i][j]]++;
        }
    }

    // Копировать элементы из A в C, которые встречаются более одного раза в B
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int element = A[i][j];
            if (frequencyMap[element] > 1) {
                C[i][j] = element;
            }
        }
    }

    // Вывод результата копирования
    std::cout << "Результат копирования:\n";
    outputMatrix(C, size);
}

// Меню программы
void menu() {
    int size;
    std::cout << "Введите размерность квадратных матриц: ";
    std::cin >> size;

    int** A = createMatrix(size);
    int** B = createMatrix(size);
    int** C = createMatrix(size);

    bool exit = false;
    while (!exit) {
        std::cout << "\n1. Ввод матрицы A с консоли\n";
        std::cout << "2. Ввод матрицы B с консоли\n";
        std::cout << "3. Ввод матрицы C с консоли\n";
        std::cout << "4. Вывод матрицы A на консоль\n";
        std::cout << "5. Вывод матрицы B на консоль\n";
        std::cout << "6. Вывод матрицы C на консоль\n";
        std::cout << "7. Загрузить матрицу A из файла\n";
        std::cout << "8. Загрузить матрицу B из файла\n";
        std::cout << "9. Загрузить матрицу C из файла\n";
        std::cout << "10. Сохранить матрицу A в файл\n";
        std::cout << "11. Сохранить матрицу B в файл\n";
        std::cout << "12. Сохранить матрицу C в файл\n";
        std::cout << "13. Редактировать элемент матрицы A\n";
        std::cout << "14. Редактировать элемент матрицы B\n";
        std::cout << "15. Редактировать элемент матрицы C\n";
        std::cout << "16. Копировать повторяющиеся элементы из A в C\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: inputMatrix(A, size); break;
        case 2: inputMatrix(B, size); break;
        case 3: inputMatrix(C, size); break;
        case 4: outputMatrix(A, size); break;
        case 5: outputMatrix(B, size); break;
        case 6: outputMatrix(C, size); break;
        case 7: loadMatrixFromFile("matrixA.txt", A, size); break;
        case 8: loadMatrixFromFile("matrixB.txt", B, size); break;
        case 9: loadMatrixFromFile("matrixC.txt", C, size); break;
        case 10: saveMatrixToFile("matrixA.txt", A, size); break;
        case 11: saveMatrixToFile("matrixB.txt", B, size); break;
        case 12: saveMatrixToFile("matrixC.txt", C, size); break;
        case 13: editMatrixElement(A); break;
        case 14: editMatrixElement(B); break;
        case 15: editMatrixElement(C); break;
        case 16: copyRepeatedElements(A, B, C, size); break;
        case 0: exit = true; break;
        default: std::cout << "Неверный выбор. Попробуйте еще раз.\n"; break;
        }
    }

    deleteMatrix(A, size);
    deleteMatrix(B, size);
    deleteMatrix(C, size);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "");

    menu();
    return 0;
}
