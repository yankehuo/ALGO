#include <iostream>
#include <cstring>
#include <algorithm>

// i (x, k/(k/x))
// nk - sum(k/x * x)
long long n, k;

int main() {
    std::cin >> n >> k;
    long long res = n * k;
    int up = 0;
    for (int x = 1; x <= n; x = up + 1) {
        up = k / x ? std::min(k / (k / x), n) : n;
        res -= (k / x) * (x + up) * (up - x + 1) / 2;
    }
    std::cout << res << std::endl;
    return 0;
}