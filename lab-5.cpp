#include <iostream>
#include <iomanip>
#include <string> 
#include <limits> 
#include <algorithm> 
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

struct GroupSummary {
    string groupNumber;
    int studentCount;
    int badGradeCount;
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

void printStudentTable(const STUDENT* students, int n) {
    const int groupWidth = 15;
    const int nameWidth = 30;
    const int gradesWidth = 20;

        for (int i = 0; i < n; ++i) {
            cout << students[i].groupNumber << " - " << students[i].name << ": ";

            string grades;
            for (int j = 0; j < 5; ++j) {
                grades += to_string(students[i].grades[j]);
                if (j < 4) grades += ", ";
            }
            cout << grades << endl;
        }
}

void printHighAverageStudents(const STUDENT* students, int n) {
    const int groupWidth = 15;
    const int nameWidth = 30;
    const int avgWidth = 15;

    for (int i = 0; i < n; ++i) {
        float avg = students[i].averageGrade();
        cout << students[i].groupNumber << ", " << students[i].name << " - " << avg << endl;
    }
}

void printGroupSummaryTable(const GroupSummary* summaries, int count, bool isHuman) {
    const int groupWidth = 15;
    const int totalWidth = 20;
    const int badGradeWidth = 25;

    auto truncate = [](const std::string& str, size_t width) -> std::string {
        if (str.size() > width) {
            return str.substr(0, width - 3) + "...";
        }
        return str;
        };

    if (isHuman) {
        cout << left << setw(groupWidth) << "Группа" << "|"
            << setw(totalWidth) << "Всего студентов" << "|"
            << setw(badGradeWidth) << "С плохими оценками" << endl;
        cout << string(groupWidth, '-') << "+"
            << string(totalWidth, '-') << "+"
            << string(badGradeWidth, '-') << endl;
        for (int i = 0; i < count; ++i) {
            cout << left << setw(groupWidth) << truncate(summaries[i].groupNumber, groupWidth) << "|"
                << setw(totalWidth) << truncate(std::to_string(summaries[i].studentCount), totalWidth) << "|"
                << setw(badGradeWidth) << truncate(std::to_string(summaries[i].badGradeCount), badGradeWidth) << endl;
        }
    }
    else {
        for (int i = 0; i < count; ++i) {
            cout << summaries[i].groupNumber << " - " << summaries[i].studentCount << " - " << summaries[i].badGradeCount << endl;
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
    if (isHuman) cout << "Полный список студентов по возрастанию номера группы:" << endl;
    printStudentTable(students, N);

    STUDENT* filteredStudents = new STUDENT[N];
    int M = 0;
    for (int i = 0; i < N; ++i) {
        if (students[i].averageGrade() > 4.0) {
            filteredStudents[M++] = students[i];
        }
    }

    stableSortByAverageGrade(filteredStudents, M);

    if (M > 0) {
        if (isHuman) cout << endl << "Студенты со средним баллом > 4.0, упорядоченные по убыванию среднего балла:" << endl;
        printHighAverageStudents(filteredStudents, M);
    }
    else {
        if (isHuman) cout << "Нет студентов со средним баллом > 4.0" << endl;
    }

    GroupSummary* summaries = new GroupSummary[N];
    int summaryCount = 0;
    for (int i = 0; i < N;) {
        GroupSummary summary;
        summary.groupNumber = students[i].groupNumber;
        summary.studentCount = 0;
        summary.badGradeCount = 0;
        while (i < N&& students[i].groupNumber == summary.groupNumber) {
            summary.studentCount++;
            if (students[i].hasBadGrades()) {
                summary.badGradeCount++;
            }
            i++;
        }
        summaries[summaryCount++] = summary;
    }

    sort(summaries, summaries + summaryCount, [](const GroupSummary& a, const GroupSummary& b) {
        return a.badGradeCount > b.badGradeCount;
        });

    if (isHuman) cout << endl << "Сводка по группам:" << endl;
    printGroupSummaryTable(summaries, summaryCount, isHuman);

    delete[] students;
    delete[] filteredStudents;
    delete[] summaries;
    return 0;
}
