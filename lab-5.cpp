#include <iostream>
#include <iomanip>
#include <string>
#include <locale.h>
#include <limits>
#define NOMINMAX
#include <Windows.h>

using namespace std;

struct STUDENT {
    string name;
    string groupNumber;
    int grades[5];
    float averageGrade() const {
        int sum = 0;
        for (int i = 0; i < 5; ++i)
            sum += grades[i];
        return static_cast<float>(sum) / 5;
    }
    bool hasBadGrades() const {
        for (int i = 0; i < 5; ++i)
            if (grades[i] == 2)
                return true;
        return false;
    }
};

void stableSortByGroup(STUDENT* students, int n) {
    for (int i = 1; i < n; ++i) {
        STUDENT key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].groupNumber > key.groupNumber) {
            students[j + 1] = students[j];
            --j;
        }
        students[j + 1] = key;
    }
}

void stableSortByAverageGrade(STUDENT* students, int n) {
    for (int i = 1; i < n; ++i) {
        STUDENT key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].averageGrade() < key.averageGrade()) {
            students[j + 1] = students[j];
            --j;
        }
        students[j + 1] = key;
    }
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "");
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0) {
        isHuman = true;
    }

    int N;
    if (isHuman) {
        cout << "Укажите количество студентов: ";
    }
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    STUDENT* students = new STUDENT[N];
    for (int i = 0; i < N; ++i) {
        if (isHuman) {
            cout << "Введите ФИО: ";
        }
        getline(cin, students[i].name);

        if (isHuman) {
            cout << "Введите номер группы: ";
        }
        cin >> students[i].groupNumber;

        if (isHuman) {
            cout << "Введите 5 оценок через пробел: ";
        }
        for (int j = 0; j < 5; ++j) {
            cin >> students[i].grades[j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    stableSortByGroup(students, N);

    for (int i = 0; i < N; ++i) {
        cout << students[i].groupNumber << " - " << students[i].name << ": ";
        for (int j = 0; j < 5; ++j) {
            cout << students[i].grades[j];
            if (j < 4) cout << ", ";
        }
        cout << endl;
    }

    STUDENT* filteredStudents = new STUDENT[N];
    int M = 0;
    for (int i = 0; i < N; ++i) {
        if (students[i].averageGrade() > 4.0) {
            filteredStudents[M++] = students[i];
        }
    }

    stableSortByAverageGrade(filteredStudents, M);

    if (M > 0) {
        for (int i = 0; i < M; ++i) {
            float avg = filteredStudents[i].averageGrade();
            cout << filteredStudents[i].groupNumber << ", "
                << filteredStudents[i].name << " - ";
            if (avg == static_cast<int>(avg)) {
                cout << static_cast<int>(avg) << endl;
            }
            else {
                cout << fixed << setprecision(1) << avg << endl;
            }
        }
    }
    else {
        cout << "NO" << endl;
    }

    for (int i = 0; i < N; ) {
        string currentGroup = students[i].groupNumber;
        int count = 0;
        int badCount = 0;
        while (i < N && students[i].groupNumber == currentGroup) {
            count++;
            if (students[i].hasBadGrades()) {
                badCount++;
            }
            i++;
        }
        cout << currentGroup << " - " << count << " - " << badCount << endl;
    }

    delete[] students;
    delete[] filteredStudents;
    return 0;
}
