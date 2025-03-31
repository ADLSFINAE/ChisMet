#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<double> zeidelMethod( vector<vector<double>>& A,
                             vector<double>& b,
                             vector<double>& x0,
                             double precision) {
    int n = A.size();
    vector<double> xn(n);
    vector<double> xs(n);

    xn = x0;
    int step = 1;
    double fault = precision + 1;


    vector<vector<double>> A_copy = A;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A_copy[i][j] = -A_copy[i][j] / A_copy[i][i];
            }
        }
        b[i] = b[i] / A_copy[i][i];
        A_copy[i][i] = 0;
    }


    while (fault > precision && step <= 1000) {
        xs = xn;


        for (int i = 0; i < n; i++) {
            xn[i] = b[i];
            step++;
            for (int j = 0; j < i; j++) {
                xn[i] += A_copy[i][j] * xn[j];
                step++;
            }
            for (int j = i + 1; j < n; j++) {
                xn[i] += A_copy[i][j] * xs[j];
                step++;
            }
        }

        fault = 0;
        for (int j = 0; j < n; j++) {
            fault += (xn[j] - xs[j]) * (xn[j] - xs[j]);
            step++;
        }
        fault = sqrt(fault);

        step++;
    }

    if (step > 1000) {
        cout << "Решение не найдено или не существует" << endl;
    }

    cout<<"STEPS COUNT: "<<step<<endl;
    return xn; 
}

vector<double> simpleIterations(vector<vector<double>>& A,
                               vector<double>& b,
                               vector<double>& x0,
                               double precision) {
    int n = A.size();
    vector<double> xn(n);
    vector<double> xs(n);

    xn = x0; 
    int step = 1;
    double fault = precision + 1;

    
    vector<vector<double>> A_copy = A;

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A_copy[i][j] = -A_copy[i][j] / A_copy[i][i];
            }
        }
        b[i] = b[i] / A_copy[i][i];
        A_copy[i][i] = 0;
    }

    
    while (fault > precision && step <= 1000) {
        xs = xn; 

        
        for (int i = 0; i < n; i++) {
            xn[i] = b[i];
            for (int j = 0; j < n; j++) {
                xn[i] += A_copy[i][j] * xs[j];
            }
        }

        
        fault = 0;
        for (int j = 0; j < n; j++) {
            fault += (xn[j] - xs[j]) * (xn[j] - xs[j]);
        }
        fault = sqrt(fault);

        step++;
    }

    if (step > 1000) {
        cout << "Решение не найдено или не существует" << endl;
    }
    cout<<"STEPS COUNT:"<<step * n * n<<endl;
    return xn; 
}

int main(){
    vector<vector<double>> A(3, vector<double>(3, 0));
    vector<double> b(3, 0);
    vector<double> x0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cin>>A[i][j];
        }
    }

    for(int i = 0; i < 3; i++){
        cin>>b[i];
    }

    x0 = {0, 0, 0};

    vector<double> ans = zeidelMethod(A,b,x0,1e-6);
    for(auto& elem : ans){
        cout<<elem<<" ";
    }
    cout<<endl;

}