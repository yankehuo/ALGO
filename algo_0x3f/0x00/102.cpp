#include <iostream>

int n, f;
const int N = 1e5 + 10;
double arr[N], s[N];
const double eps = 1e-6;

bool check(double avg) {
    for (int i = 1; i <= n; ++i)  {
        s[i] = s[i - 1] + arr[i] - avg;
    }
    double minval = 1e6;
    for (int i = f; i <= n; ++i) {
        minval = std::min(minval, s[i - f]);
        if (s[i] - minval >= 0) {
            return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n >> f;
    double minval = 2000, maxval = 1; 
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
        minval = std::min(minval, arr[i]);
        maxval = std::max(maxval, arr[i]);
    }
    double l = minval, r = maxval;
    while (l + eps < r) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    std::cout << (int)(r * 1000) << std::endl;

    return 0;
}