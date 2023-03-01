#include <iostream>
#include <cmath>

int t;
long long N, A, B;
using PLL = std::pair<long long, long long>;

double distance(PLL point1, PLL point2) {
    double dx = point1.first - point2.first;
    double dy = point1.second - point2.second;
    double res = sqrt(dx * dx + dy * dy);
    return res;
}

// 编号为m的房屋在n级城市中的位置
PLL calc(long long n, long long m) {
    if (n == 0) {
        return {0, 0};
    }
    // first calc n-1, m%cnt
    // long long
    long long cnt = 1ll << (2 * n - 2), len = 1ll << (n - 1);
    auto p = calc(n - 1, m % cnt);
    auto x = p.first, y = p.second;
    auto z = m / cnt;
    if (z == 0) {
        return {y, x};
    }
    if (z == 1) {
        return {x, y + len};
    }
    if (z == 2) {
        return {x + len, y + len};
    }
    return {-y + 2 * len - 1, -x + len - 1};

}

int main() {
    std::cin >> t;
    while (t--) {
        std::cin >> N >> A >> B;
        double dis = distance(calc(N, A - 1), calc(N, B - 1));
        printf("%.0lf\n", dis * 10);
    }

    return 0;
}