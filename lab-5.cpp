#include <iostream>
#include <iomanip>
#include <string>
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

void printTable(STUDENT* students, int n) {
    const int nameWidth = 20;
    const int groupWidth = 10;
    const int gradeWidth = 20;
    const int avgWidth = 10;

    cout << setw(groupWidth) << "Группа" << "|"
        << setw(nameWidth) << "Имя" << "|"
        << setw(gradeWidth) << "Оценки" << "|"
        << setw(avgWidth) << "Сред." << endl;
    cout << string(groupWidth, '_') << "|"
        << string(nameWidth, '_') << "|"
        << string(gradeWidth, '_') << "|"
        << string(avgWidth, '_') << endl;

    for (int i = 0; i < n; ++i) {
        cout << setw(groupWidth) << students[i].groupNumber << "|"
            << setw(nameWidth) << students[i].name << "|";

        string grades;
        for (int j = 0; j < 5; ++j) {
            grades += to_string(students[i].grades[j]);
            if (j < 4) grades += ", ";
        }
        cout << setw(gradeWidth) << grades << "|";

        float avg = students[i].averageGrade();
        if (avg == static_cast<int>(avg)) {
            cout << setw(avgWidth) << static_cast<int>(avg) << endl;
        }
        else {
            cout << setw(avgWidth) << fixed << setprecision(1) << avg << endl;
        }
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
    if (isHuman) cout << "Полный список студентов:" << endl;
    printTable(students, N);

    STUDENT* filteredStudents = new STUDENT[N];
    int M = 0;
    for (int i = 0; i < N; ++i) {
        if (students[i].averageGrade() > 4.0) {
            filteredStudents[M++] = students[i];
        }
    }

    stableSortByAverageGrade(filteredStudents, M);

    if (M > 0) {
        if (isHuman) cout << endl << "Студенты со средним баллом > 4.0:" << endl;
        printTable(filteredStudents, M);
    }
    else {
        if (isHuman) cout << "Нет студентов со средним баллом > 4.0" << endl;
    }

    if (isHuman) cout << endl << "Сводка по группам:" << endl;
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
        if (isHuman) {
            cout << "Группа " << currentGroup << ": всего студентов - "
                << count << ", с плохими оценками - " << badCount << endl;
        }
    }

    delete[] students;
    delete[] filteredStudents;
    return 0;
}
