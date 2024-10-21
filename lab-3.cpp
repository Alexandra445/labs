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
    double step = (x2 - x1) / 14;   //  Задаём шаг 
    double FirstArr[15], SecondArr[15];  //  Объявляем массивы 
    for (int i = 0, j = 14; i < 15; i++, j--)
    {
        double X = x1 + i * step;   //  Элемент массива 
        //  Запускаем функцию F 
        FirstArr[i] = Function(X, a, b, c);
        SecondArr[j] = Function(-X, a, b, c);

        int A = int(trunc(a)), B = int(trunc(b)), C = int(trunc(c));    //  Здесь мы для дальнейших побитовых операций перевели double в int 
        if (((A | B) & (A | C)) == 0) {    // Проверка на округление 
            FirstArr[i] = trunc(FirstArr[i]);       // Округление до целого, если целая часть 
            SecondArr[j] = trunc(SecondArr[j]);     // trunc оставляет только целое значение (округляет вниз) 
        }
        else {
            FirstArr[i] = round(FirstArr[i] * 100) / 100;             // Округление до 2 знаков 
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
    for (int i = 0; i < 15; i++)SortArr[i] = FirstArr[i];  //  Чтобы не портить исходный массив 
    //  Сортировка выбором 
    for (int i = 0; i < 15; i++)
        for (int j = 14; j > i; j--)
            if (SortArr[i] > SortArr[j])swap(SortArr[i], SortArr[j]);   //  swap меняет местами значения 2-х элементов 


    //  Поиск повторов 
    int Replay = 0;     //  Количество повторов изначально 0 
    double Memory = FirstArr[0];    //  Запоминаем значение повтора 
    bool prov = false;
    for (int i = 1; i < 15; i++)
    {
        if ((FirstArr[i] == Memory) && (prov == false))  //  prov == false чтобы исключить подсчёт уже знакомых повторов 
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
    int Two = -1;
    for (int i = 0; i < 13; i++)     //  До 13-ти, т.к. последовательностью будем считать хотя бы 3 элемента 
    {
        int ind = 0;
        for (int j = i; j < i + 3; j++)   //  Допустим что последовательность может быть в середине массива и содержать хотя бы 3 значения 
        {
            int k = 1;
            while (k <= FirstArr[i])k *= 2;  //  Степени 2 

            if (FirstArr[j] == k)ind++;
            else break;     //  Если последовательность нарушается, то переходим к следующему элементу 
        }
        if (ind == 3)
        {
            Two = i;
            break;      //  Поскольку нам нужно найти лишь 1 индекс, то дальше нет смысла искать 
        }
    }

    //Перераспределение 
    double NewFirstArr[15], NewSecondArr[15];   //  Новые массивы 
    double OldFirstArr[15], OldSecondArr[15];   //  Запоминаем старые массивы для вывода 
    for (int i = 0; i < 15; i++)
    {
        OldFirstArr[i] = FirstArr[i];
        OldSecondArr[i] = SecondArr[i];
    }
    int ind = 0;
    for (int i = 0; i < 15; i++)             //  Заполняем 1-й массив значениями из 1-го массива 
    {
        if (FirstArr[i] < 0)
        {
            NewFirstArr[ind] = FirstArr[i]; //  Запоминаем в новый 1-й массив значения 
            FirstArr[i] = 0;                //  Стираем их из прошлого 
            ind++;
        }
    }
    for (int i = 0; i < 15; i++)             //  Заполняем 1-й массив значениями из 2-го массива 
    {
        if ((ind < 15) && (SecondArr[i] < 0))
        {
            NewFirstArr[ind] = SecondArr[i];
            SecondArr[i] = 0;
            ind++;
        }
    }
    for (int i = ind + 1; i < 15; i++)NewFirstArr[i] = 0;     //  Заполняем нулями 
    ind = 0;
    for (int i = 0; i < 15; i++)             //  Заполняем 2-й массив значениями из 2-го массива 
    {
        if (SecondArr[i] > 0)
        {
            NewSecondArr[ind] = SecondArr[i];
            SecondArr[i] = 0;
            ind++;
        }
    }
    for (int i = 0; i < 15; i++)             //  Заполняем 2-й массив значениями из 1-го массива 
    {
        if ((ind < 15) && (FirstArr[i] > 0))
        {
            NewSecondArr[ind] = FirstArr[i];
            FirstArr[i] = 0;
            ind++;
        }
    }
    for (int i = ind + 1; i < 15; i++)NewSecondArr[i] = 0;    //  Заполняем нулями 


    if (isHuman) {
        cout << "Первый массив: ";
        for (int i = 0; i < 15; ++i) {
            cout << OldFirstArr[i] << " ";
        }
        cout << endl;
        
        cout << "Второй массив: ";
        for (int i = 0; i < 15; ++i) {
            cout << OldSecondArr[i] << " ";
        }
        cout << endl;
        
        cout << "Минимумы: " << mn_1 << endl << mn_2 << endl << mn_3 << endl;
        
        cout << "Сортировка: ";
        for (int i = 0; i < 15; ++i) {
            cout << SortArr[i] << " ";
        }
        cout << endl;
        
        cout << "Повторы: " << Replay << endl;
        cout << "Степень 2: " << Two << endl;
        
        cout << "Перераспределение 1 массива: ";
        for (int i = 0; i < 15; ++i) {
            cout << NewFirstArr[i] << " ";
        }
        cout << endl;
        
        cout << "Перераспределение 2 массива: ";
        for (int i = 0; i < 15; ++i) {
            cout << NewSecondArr[i] << " ";
        }
        cout << endl;
    }
    else {
        for (int i = 0; i < 15; ++i) {
            cout << OldFirstArr[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < 15; ++i) {
            cout << OldSecondArr[i] << " ";
        }
        cout << endl;

        cout << mn_1 << endl << mn_2 << endl << mn_3 << endl;

        for (int i = 0; i < 15; ++i) {
            cout << SortArr[i] << " ";
        }
        cout << endl;

        cout << Replay << endl;
        cout << Two << endl;

        for (int i = 0; i < 15; ++i) {
            cout << NewFirstArr[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < 15; ++i) {
            cout << NewSecondArr[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
