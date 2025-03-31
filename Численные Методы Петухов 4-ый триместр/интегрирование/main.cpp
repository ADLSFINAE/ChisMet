#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <fstream>
using namespace std;

double func(double  x, double  y)
{ return y + 5; }

int main()
{
    std::ofstream out; 
    out.open("hello.txt");

    double  x, y,X0,Y0, h = 0.1, k[4];


    cin>>X0>>Y0;

    x = X0;
    y = Y0;

    for(int i = 0;i < 10; i++)
    {
        k[0] = h * func(x, y);
        k[1] = h * func(x + (h/2), y + (k[0]/2));
        k[2] = h * func(x + (h/2), y + (k[1]/2));
        k[3] = h * func(x + (h/2), y + k[2]);

        x += h;
        y = y + (k[0] + k[1] * 2 + k[2] * 2 + k[3]) / 6;

        cout<<"K0: "<<k[0]<<" K1: "<<k[1]<<" K2: "<<k[2]<<" K3: "<<k[3]<<endl;
        cout<<x<<" "<<y<<endl;
        if (out.is_open())
        {
            out <<x<<" "<<y<< std::endl;
        }
    }
    out.close();
    std::cout << "File has been written" << std::endl;
}
