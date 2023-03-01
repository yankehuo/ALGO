#include <iostream>

const int N = 1e5 + 10;
long long a[N]{};
long long b[N]{};
int n;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (i == 1) {
            b[i] = a[i];
        }
        else {
            b[i] = a[i] - a[i - 1];
        }
    }
    long long p = 0, q = 0;
    for (int i = 2; i <= n; ++i) {
        if (b[i] > 0) p += b[i];
        else q -= b[i];
    }
    std::cout << std::max(p, q) << std::endl;
    std::cout << abs(p - q) + 1 << std::endl;
    return 0;
}