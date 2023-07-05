#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

double func(double x)
{
    return (pow(x, 4) - 18 * pow(x, 2) - 6);
}
double Dichotomy(double x0, double x1, double eps)
{
    double left = x0, right = x1, x, fl, fr, f;
    int iter = 0;
    cout << "THE DICHOTOMY METHOD" << endl << "x0= " << x0 << endl << "x1= " << x1 << endl;
    do {
        x = (left + right) / 2;
        f = func(x);
        if (f > 0) right = x;
        else left = x;
        iter++;
    } while (fabs(f) > eps && iter < 20000);
    cout << iter << " iterations" << endl;
    cout << "---------------------------";
    return x;
}

double Newton(double x, double eps)
{
    double f, df; int iter = 0;
    cout << endl << "NEWTON'S METHOD" << endl << "x0 = " << x << endl;
    do {
        f = func(x);
        df = (4 * pow(x, 3) - 36 * x);
        x = x - f / df;
        iter++;
    } while (fabs(f) > eps && iter < 20000);
    cout << iter << " iterations" << endl;
    cout << "---------------------------";
    return x;
}

double Chord(double x0, double x1, double eps)
{
    double x = x1, f0, f;
    int iter = 0;
    cout << endl << "THE CHORD METHOD" << endl << "x0= " << x0 << endl << "x1= " << x1 << endl;
    do {
        f = func(x);
        f0 = (pow(x0, 4) - 18 * pow(x0, 2) - 6);
        x = x - f / (f - f0) * (x - x0);
        iter++;
    } while (fabs(f) > eps && iter < 20000);
    cout << iter << " iterations" << endl;
    cout << "---------------------------";
    return x;
}


int main()
{
    cout << Dichotomy(-10.0, 10.0, 0.000001);
    cout << Newton(10.0, 0.000001);
    cout << Chord(10.0, 1.0, 0.000001);
    cin.get(); return 0;
}