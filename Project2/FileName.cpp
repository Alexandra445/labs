#include <cmath> 
#include <cstring>
#include <iomanip> 
#include <iostream>  
#include <limits>

int n, x, f, mx, mn, k1, k2, k3, p1, p2, p3;
double sum;

int main(int argc, const char* argv[]) {
    setlocale(LC_ALL, "RUS");

    bool isHuman = true;

    if (argc > 1 && strcmp(argv[1], "false") == 0) {
        isHuman = false;
    }

    if (isHuman) {
        std::cout << "������� ���������� ����� � ������������������: " << std::endl;
    }

    std::cin >> n;
    // ���������� ���������� �������� ���� ������ int
    mn = std::numeric_limits<int>::max();
    mx = std::numeric_limits<int>::min();

    if (isHuman) {
        std::cout << "������� ������������������ ������������� ����� �����: " << std::endl;
    }

    for (size_t i = 0; i < n; ++i) {

        std::cin >> x;

        f = 0;
        if (x == 2) {
            if (isHuman) {
                std::cout << x << " �������� ������� ������." << std::endl;
            }
            else {
                std::cout << x << std::endl;
            }
        }
        else if (x > 2 && x % 2 != 0) {  // ���������� ������ �����, ����� 2
            int sqrt_x = std::sqrt(x);  // ��������� ������ ���� ���
            for (int j = 3; j <= sqrt_x; j += 2) {  // ��������� ������ �������� �����
                if (x % j == 0) {
                    f = 1;
                    break;  // ���������� �������� ��� ���������� ��������
                }
            }
            if (f == 0) {
                if (isHuman) {
                    std::cout << x << " �������� ������� ������." << std::endl;
                }
                else {
                    std::cout << x << std::endl;
                }
            }
        }

        // ������������ ���� �����
        sum += x;

        // ����� �������� � ���������
        mn = std::min(mn, x);
        mx = std::max(mx, x);

        // ���������� �����, ������� 5
        if (x % 5 == 0) {
            k1++;
        }

        // ��������, �������� �� ����� �������� ������
        double y = x;
        while (y > 1) {
            y /= 2;
        }
        if (y == 1) {
            k2++;
        }

        // ���������� �����, ����������� ����� ���� ����������
        p1 = p2;
        p2 = p3;
        p3 = x;
        if (i >= 2) {
            if (p3 > p1 + p2) {
                k3++;
            }
        }
    }

    if (isHuman) {
        std::cout << "������� �������������� �������� �����: " << std::fixed << std::setprecision(2) << (sum) / n << std::endl
            << "������� ����� ���������� � ���������: " << mx - mn << std::endl
            << "���������� �����, ������� ����� 5: " << k1 << std::endl
            << "���������� �����, ���������� �������� ������: " << k2 << std::endl
            << "���������� �����, ����������� ����� ���� �������������� ������ ������������������: " << k3 << std::endl;
    }
    else {
        std::cout << std::fixed << std::setprecision(2) << (sum) / n << std::endl
            << mx - mn << std::endl
            << k1 << std::endl
            << k2 << std::endl
            << k3 << std::endl;
    }

    return 0;
}