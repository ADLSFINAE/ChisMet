#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int N = 11;
const double y = 0.5;
const double h = 0.1;
const double x0 = 0;


//теплопроводности
double F(double x) {
    return x * sin(3.1415 * x);
}

int main() {
    double Uin[N][N];

    ofstream outFile("output.txt");

    for (int n = 0; n < N; ++n) {
        Uin[0][n] = 0;
        Uin[10][n] = 1.0 / 12;
    }

    outFile << "n = 0" << endl;
    for (int i = 1; i < 10; ++i) {
        Uin[i][0] = F(x0 + h * i);
        outFile << Uin[i][0] << endl;
    }

    outFile << endl;
    for (int n = 0; n < 10; ++n) {
        outFile << "n = " << n + 1 << endl;
        for (int i = 1; i < 10; ++i) {
            Uin[i][n + 1] = (1 - 2 * y) * Uin[i][n] + y * (Uin[i - 1][n] + Uin[i + 1][n]);
            outFile << Uin[i][n + 1] << endl;
        }
    }

    outFile.close();

    return 0;
}


