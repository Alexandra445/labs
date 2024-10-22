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

    //  Ввод 
    double x1, x2, a, b, c;
    cin >> x1 >> x2 >> a >> b >> c;
    //  Создание массивов 
    double step = (x2 - x1) / 14;
    double FirstArr[15], SecondArr[15];
    for (int i = 0, j = 14; i < 15; i++, j--)
    {
        double X = x1 + i * step;   //  Элемент массива 
        //  Запускаем функцию F 
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

    //  Минимумы пятерок 1-го массива 
    //  Т.к. min принимает только 2 аргумента, мы в min помещаем ещё один min 
    double mn_1 = min(FirstArr[0], min(FirstArr[1], min(FirstArr[2], min(FirstArr[3], FirstArr[4]))));
    double mn_2 = min(FirstArr[5], min(FirstArr[6], min(FirstArr[7], min(FirstArr[8], FirstArr[9]))));
    double mn_3 = min(FirstArr[10], min(FirstArr[11], min(FirstArr[12], min(FirstArr[13], FirstArr[14]))));

    //  Сортировка 
    double SortArr[15];
    for (int i = 0; i < 15; i++)  SortArr[i] = FirstArr[i];
    //  Сортировка выбором 
    for (int k = 0; k < 14; k++) {
        int imin = k;
        for (int i = k + 1; i < 15; i++) {
            if (SortArr[i] < SortArr[imin]) {
                imin = i;
            }
        }
        if (imin != k)
        {
            int tmp = SortArr[k];
            SortArr[k] = SortArr[imin];
            SortArr[imin] = tmp;
        }

    }

    //  Поиск повторов 
    int Replay = 0;
    double Memory = FirstArr[0];
    bool prov = false;
    for (int i = 1; i < 15; i++)
    {
        if ((FirstArr[i] == Memory) && (prov == false))
        {
            Replay++;
            prov = true;
        }
        else
        {
            Memory = FirstArr[i];
            prov = false;
        }
    }

    //  Поиск степеней 2
    int two = -1;
    for (int i = 0; i < 15; i++) {
        bool isPowerOfTwo = true;
        int expectedPower = 1;  // <- первая степень двойки

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

    //Перераспределение 
    double NewFirstArr[15], NewSecondArr[15];
    double OldFirstArr[15], OldSecondArr[15];
    for (int i = 0; i < 15; i++)
    {
        OldFirstArr[i] = FirstArr[i];
        OldSecondArr[i] = SecondArr[i];
    }
    int ind = 0;
    for (int i = 0; i < 15; i++)
    {
        if (FirstArr[i] < 0)
        {
            NewFirstArr[ind] = FirstArr[i];
            FirstArr[i] = 0;
            ind++;
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if ((ind < 15) && (SecondArr[i] < 0))
        {
            NewFirstArr[ind] = SecondArr[i];
            SecondArr[i] = 0;
            ind++;
        }
    }
    for (int i = ind + 1; i < 15; i++)NewFirstArr[i] = 0;
    ind = 0;
    for (int i = 0; i < 15; i++)
    {
        if (SecondArr[i] > 0)
        {
            NewSecondArr[ind] = SecondArr[i];
            SecondArr[i] = 0;
            ind++;
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if ((ind < 15) && (FirstArr[i] > 0))
        {
            NewSecondArr[ind] = FirstArr[i];
            FirstArr[i] = 0;
            ind++;
        }
    }
    for (int i = ind + 1; i < 15; i++)NewSecondArr[i] = 0;


    if (isHuman) {
        cout << "Первый массив: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << OldFirstArr[i] << " ";
            }
            else {
                cout << OldFirstArr[i];
            }
        }
        cout << endl;

        cout << "Второй массив: ";
        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << OldSecondArr[i] << " ";
            }
            else {
                cout << OldSecondArr[i];
            }
        }
        cout << endl;

        cout << "Минимумы: " << mn_1 << endl << mn_2 << endl << mn_3 << endl;

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
                cout << OldFirstArr[i] << " ";
            }
            else {
                cout << OldFirstArr[i];
            }
        }
        cout << endl;

        for (int i = 0; i < 15; ++i) {
            if (i != 14) {
                cout << OldSecondArr[i] << " ";
            }
            else {
                cout << OldSecondArr[i];
            }
        }
        cout << endl;

        cout << mn_1 << endl << mn_2 << endl << mn_3 << endl;

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
