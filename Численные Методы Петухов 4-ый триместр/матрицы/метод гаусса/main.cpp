#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> gauss(vector<vector<double>> a, vector<double>& y) {
    int n = a.size();
    vector<double> x(n);
    double eps = 1e-6;

    int k = 0;
    while (k < n) {
        double max = abs(a[k][k]);
        int index = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(a[i][k]) > max) {
                max = abs(a[i][k]);
                index = i;
            }
        }


        if (abs(a[k][k]) < eps) {
            cout << "NO ANS";
            cout << index << " ZERO VECTOR AT INDEX" << endl;
            return {};
        }
        for (int j = 0; j < n; j++) {
            swap(a[k][j], a[index][j]);
        }
        swap(y[k], y[index]);

        for (int i = k; i < n; i++) {
            double temp = a[i][k];
            if (abs(temp) < eps) {
                continue;
            }
            for (int j = k; j < n; j++) {
                a[i][j] /= temp;
            }
            y[i] /= temp;

            if (i == k) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                a[i][j] -= a[k][j];
            }
            y[i] -= y[k];
        }

        k++;
    }

    for (k = n - 1; k >= 0; k--) {
        x[k] = y[k];
        for (int i = 0; i < k; i++) {
            y[i] -= a[i][k] * x[k];
        }
    }

    return x;
}

int main() {
    int n = 3;


    vector<vector<double>> a(n, vector<double>(n));

    a = {
        { 3,2,1 },
        { -1.5, 7, 4 },
        { 2, 6, 9 }
    };


    vector<double> y(n);

    y = { 2, 6, 3 };

    vector<double> x = gauss(a, y);

    cout<<x[0] * a[0][0] + x[1] * a[0][1] + x[2] * a[0][2]<<endl;
    cout<<x[0] * a[0][0] + x[1] * a[0][1] + x[2] * a[0][2]<<endl;
    cout<<x[0] * a[0][0] + x[1] * a[0][1] + x[2] * a[0][2]<<endl;

    cout << "SOLUTION: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]=" << x[i] << endl;
    }

    return 0;
}
