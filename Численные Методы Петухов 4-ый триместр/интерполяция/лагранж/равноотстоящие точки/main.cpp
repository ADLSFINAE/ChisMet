#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int n, i;
    vector<double> x, y;
    double X, t, v, S = 0; // X - промежуточная точка, v - результат, S - сумма
    int c = 1, sign;

    cout << "COUNT DOTS: ";
    cin >> n;


    cout << "WRITE X and Y: ";
    for (i = 0; i < n; i++) {
        double xi, yi;
        cin >> xi >> yi;
        x.push_back(xi);
        y.push_back(yi);
    }


    cout << "X0 PARAM INTER : ";
    cin >> X;

    t = (X - x[0]) / (x[1] - x[0]);

    v = t;
    for (i = 1; i < n; i++) {
        v *= (t - i);
    }

    for (i = 0; i < n; i++) {
        if ((n - 1 - i) % 2 == 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        c = factorial(i) * factorial(n - 1 - i) * sign;
        S += y[i] / ((t - i) * c);
    }

    v *= S;

    cout << "ANS" << v << endl;

    return 0;
}

