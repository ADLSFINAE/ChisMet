#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class ShootingMethod {
private:
    double x0 = 0;
    double x1 = 1;
    double h = 0.01;
    double E = 1e-6;
    ofstream out_num; // Файл для численного решения
    ofstream out_analytical; // Файл для аналитического решения

public:
    // Функция f_xy: dy/dx = z
    double f_xy(double x, double y, double z) {
        return z;
    }

    // z_xy: dz/dx = 4y
    double z_xy(double x, double y, double z) {
        return 4 * y;
    }

    // Метод Рунге-Кутта 4-го порядка
    double RungeKutta(double z0) {
        double x = x0;
        double y = 1; // y(0) = 1
        double z = z0; // y'(0) = z0

        while (x <= x1) {
            double k1 = h * f_xy(x, y, z);
            double q1 = h * z_xy(x, y, z);

            double k2 = h * f_xy(x + h / 2, y + k1 / 2, z + q1 / 2);
            double q2 = h * z_xy(x + h / 2, y + k1 / 2, z + q1 / 2);

            double k3 = h * f_xy(x + h / 2, y + k2 / 2, z + q2 / 2);
            double q3 = h * z_xy(x + h / 2, y + k2 / 2, z + q2 / 2);

            double k4 = h * f_xy(x + h, y + k3, z + q3);
            double q4 = h * z_xy(x + h, y + k3, z + q3);

            y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            z += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
            x += h;
        }

        return y; // y(1)
    }

    // Метод секущих для нахождения y'(0)
    double Solve() {
        double z0_guess1 = 0;
        double z0_guess2 = 1;
        double y1, y2;

        y1 = RungeKutta(z0_guess1);
        y2 = RungeKutta(z0_guess2);

        double z0;
        do {
            z0 = z0_guess2 - (y2 - cosh(2 * x1)) * (z0_guess2 - z0_guess1) / (y2 - y1);
            z0_guess1 = z0_guess2;
            z0_guess2 = z0;

            y1 = y2;
            y2 = RungeKutta(z0);
        } while (abs(y2 - cosh(2 * x1)) > E);

        return z0;
    }

    // Аналитическое решение
    double AnalyticalSolution(double x) {
        double C1 = (cosh(2 * x1) - exp(-2 * x1)) / (exp(2 * x1) - exp(-2 * x1));
        double C2 = 1 - C1;
        return C1 * exp(2 * x) + C2 * exp(-2 * x);
    }

    // Сохранение численного и аналитического решений
    void SaveSolution(double z0) {
        out_num.open("numerical_solution.txt");
        out_analytical.open("analytical_solution.txt");

        double x = x0;
        double y = 1; // y(0) = 1
        double z = z0; // y'(0) = z0

        while (x <= x1) {
            double y_analytical = AnalyticalSolution(x);

            // Запись численного решения
            out_num << x << " " << y << endl;

            // Запись аналитического решения
            out_analytical << x << " " << y_analytical << endl;

            // Шаги метода Рунге-Кутта
            double k1 = h * f_xy(x, y, z);
            double q1 = h * z_xy(x, y, z);

            double k2 = h * f_xy(x + h / 2, y + k1 / 2, z + q1 / 2);
            double q2 = h * z_xy(x + h / 2, y + k1 / 2, z + q1 / 2);

            double k3 = h * f_xy(x + h / 2, y + k2 / 2, z + q2 / 2);
            double q3 = h * z_xy(x + h / 2, y + k2 / 2, z + q2 / 2);

            double k4 = h * f_xy(x + h, y + k3, z + q3);
            double q4 = h * z_xy(x + h, y + k3, z + q3);

            y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            z += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
            x += h;
        }

        out_num.close();
        out_analytical.close();
    }
};

int main() {
    ShootingMethod solver;

    double z0 = solver.Solve();
    cout << "Найденное начальное значение y'(0): " << z0 << endl;

    solver.SaveSolution(z0);

    return 0;
}