#include<iostream> 
#include<cmath> 
#include<iomanip> 
#include <cstring>

using namespace std;

int n, x, f, mx, mn, k1, k2, k3, p1, p2, p3;
double sum, y;

int main(int argc, const char* argv[])
{
    setlocale(LC_ALL, "RUS");

    bool isHuman = true;

    if (argc > 1 && strcmp(argv[1], "false") == 0) {
        isHuman = false;
    }

    if (isHuman) {
        cout << "������� ���������� ����� � ������������������: " << endl;
    }
    cin >> n;
    mn = 1000000;

    if (isHuman) {
        cout << "������� ������������������ ������������� ����� �����: " << endl;
    }

    for (int i = 0; i < n; i++) {
        cin >> x;

        // ������� ������� ����� ������������������ 
        f = 0;
        if (x != 1) {
            for (int j = 2; j <= sqrt(x); j++) {
                if (x % j == 0) {
                    f = 1;
                }
            }
            if (f == 0) {
                cout << x << " �������� ������� ������." << endl;
            }
        }

        // ������� ����� ���� ��������� ������������������ 
        sum += x;
        // ������� min � max � ������������������ 
        mn = min(mn, x);
        mx = max(mx, x);
        // ������� ���������� ����� ������� 5 
        if (x % 5 == 0) {
            k1++;
        }
        // ������� ���������� ����� ���������� �������� ������ 
        y = x;
        while (y > 1) {
            y /= 2;
        }
        if (y == 1) {
            k2++;
        }
        // ������� ���������� �����, ����������� ����� ���� �������������� ������ ������������������ 
        p1 = p2;
        p2 = p3;
        p3 = x;
        if (i >= 2) {
            if (p3 > p1 + p2) {
                k3++;
            }
        }
    }

    cout << "������� �������������� �������� �����: " << fixed << setprecision(2) << (sum) / n << endl;
    cout << "������� ����� ���������� � ���������: " << mx - mn << endl;
    cout << "���������� �����, ������� ����� 5: " << k1 << endl;
    cout << "���������� �����, ���������� �������� ������: " << k2 << endl;
    cout << "���������� �����, ����������� ����� ���� �������������� ������ ������������������: " << k3 << endl;

    return 0;
}