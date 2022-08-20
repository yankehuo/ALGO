#include <iostream>
using namespace std;
const double eps = 1e-8;
double x;

int main() {
    cin >> x;
    double l = -100, r = 100;
    while (l + eps < r) { 
        double mid = (l + r) / 2;
        if (mid * mid * mid >= x) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    printf("%.6lf\n", l);
}
