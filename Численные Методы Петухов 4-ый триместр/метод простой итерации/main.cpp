#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


double norm(const vector<double>& x) {
    double sum = 0;
    for (double val : x) {
        sum += val * val;
    }
    return sqrt(sum);
}
vector<double> vecx1;
vector<double> vecx2;
vector<double> vecx3;

vector<double> simpleIterations(const vector<vector<double>>& A,
                                const vector<double>& b,
                                const vector<double>& x0,
                                double eps, int maxIter) {
    int n = 3;
    vector<double> x(n);
    vector<double> xPrev(n);

    x = x0;

    for(int k = 0; k < maxIter; k++){
        xPrev = x;


        for(int i = 0; i < n; i++){
            double sum = b[i];
            for(int j = 0; j < n; j++){
                if(i != j)
                  sum -= A[i][j] * xPrev[j];
            }
            x[i] = sum / A[i][i];

            if(i == 0){
                vecx1.push_back(x[i]);
            }
            if(i == 1){
                vecx2.push_back(x[i]);
            }
            if(i == 2){
                vecx3.push_back(x[i]);
            }


        }



        if(abs((norm(x) - norm(xPrev)) / norm(xPrev)) < eps){
            cout <<"ITER COUNT: "<< k * n * n << endl;

            return x;
        }
    }

    cout << "NO ANS" << endl;
    return x;
}

int main() {
    vector<vector<double>> A = {
        { 3, 2, 1 },
        { -1.5, 7, 4 },
        { 2, 6, 9 }
    };
    vector<double> b = { 2, 6, 3 };


    vector<double> x0 = { 0, 0, 0 };


    double eps = 1e-6;
    int maxIter = 50;

    vector<double> solution = simpleIterations(A, b, x0, eps, maxIter);

    // Выводим решение
    cout << "Solution: " << endl;
    for (int i = 0; i < static_cast<int>(solution.size()); i++) {
        cout << "x[" << i << "] = " << solution[i] << endl;
    }

    cout<<endl<<endl;
    cout<<"CHECKING"<<endl;

    cout<<A[0][0] * solution[0] + A[0][1] * solution[1] + A[0][2] * solution[2]<<endl;
    cout<<A[1][0] * solution[0] + A[1][1] * solution[1] + A[1][2] * solution[2]<<endl;
    cout<<A[2][0] * solution[0] + A[2][1] * solution[1] + A[2][2] * solution[2]<<endl;

    cout<<endl<<endl;
    cout<<"HISTORY OF OPERATIONS: "<<endl;
    cout<<vecx1.size()<<" "<<vecx2.size()<<" "<<vecx3.size()<<endl;
    for(int i = 0; i < static_cast<int>(vecx1.size()); i++){
        cout<<"x1: "<<vecx1[i]<<" x2: "<<vecx2[i]<<" x3: "<<vecx3[i]<<endl;
    }

    return 0;
}