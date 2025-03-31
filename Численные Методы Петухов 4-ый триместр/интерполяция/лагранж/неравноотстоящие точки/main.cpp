#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n, i, k;
    vector<double> x, y;
    double X, v, S = 0, D; // X - промежуточная точка, v - результат, S - сумма

    cout << "COUNT OF THE DOTS: ";
    cin >> n;


    cout << "WRITE X and Y: "<<endl;
    for (i = 0; i < n; i++) {
        double xi, yi;
        cin >> xi >> yi;
        x.push_back(xi);
        y.push_back(yi);
    }


    cout << "X0 PARAM INTER: ";
    cin >> X;

    v = X - x[0];
    for (i = 1; i < n; i++) {
        v *= (X - x[i]);
    }

    for (i = 0; i < n; i++) {
        if(i != 0){
            D = x[i] - x[0];
        }
        else{
            D = X - x[0];
        }
        for (k = 1; k < n; k++) {
            if (k != i) {
                D *= (x[i] - x[k]);
            } else {
                D *= (X - x[i]);
            }
        }
        S += y[i] / D;
    }

    v *= S;
    cout << "ANS "<< v << endl;

    return 0;
}
