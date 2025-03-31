#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int N = 10, M = 10;
const double h = 0.1, tau = 0.05;

// Функция F(x)
double F(double x) {
    return x * cos(x);
}

// Функция Ф(x)
double Ф(double x) {
    return 0.5 * x * (1 + x);
}

int main() {
    double u0[N], u1[N], u2[N];
    double alf = tau / h, x = 0;

    // Инициализация массива u0
    for (int n = 0; n < N; n++) {
        x = n * h;
        u0[n] = F(x);
        cout << u0[n] << endl;
    }
    cout << endl;

    // Инициализация массива u1
    for (int i = 1; i < N - 1; i++) {
        x = i * h;
        u1[i] = (1 - pow(alf, 2)) * F(x) + pow(alf, 2) * 0.5 * (F((i + 1) * h) + F((i - 1) * h)) + tau * Ф(x);
    }
    u1[0] = 2 * tau * tau;
    u1[N - 1] = 1;

    for (int i = 0; i < N; i++) {
        cout << u1[i] << endl;
    }
    cout << endl;

    // Основной цикл по времени
    for (int n = 1; n < M; n++) {
        u2[0] = 2 * tau * tau * n;
        u2[N - 1] = 1;
        cout << "n = " << n << endl;
        cout << u2[0] << endl;

        for (int i = 1; i < N - 1; i++) {
            x = i * h;
            u2[i] = 2 * u1[i] - u0[i] + pow(h, 2) * (u1[i + 1] - 2 * u1[i] + u1[i - 1]);
            cout << u2[i] << endl;
        }

        // Обновление массивов
        for (int j = 0; j < N; j++) {
            u0[j] = u1[j];
            u1[j] = u2[j];
        }

        cout << u2[N - 1] << endl;
        cout << endl;
    }

    cin.get(); // Ожидание ввода перед завершением
    return 0;
}
