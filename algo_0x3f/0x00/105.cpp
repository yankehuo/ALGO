#include <iostream>
#include <algorithm>

int n, m, t;
const int N = 1e5 + 10;
long long r[N], c[N]; // row col
long long s[N];

long long calc(long long *arr, long long num) {
    for (int i = 1; i <= num; ++i) {
        s[i] = s[i - 1] + arr[i] - arr[0] / num;
    }
    std::sort(s + 1, s + num);
    long long res = 0;
    for (int i = 1; i <= num; ++i) {
        res += abs(s[i] - s[num + 1 >> 1]);
    }
    return res;
}

int main() {
    int x, y;
    std::cin >> n >> m >> t;
    while (t--) {
        std::cin >> x >> y;
        ++r[x], ++c[y];
    }
    for (int i = 1; i <= n; ++i) {
            r[0] += r[i];
    }
    for (int i = 1; i <= m; ++i) {
        c[0] += c[i];
    }
    if (r[0] % n == 0 && c[0] % m == 0) {
        std::cout << "both " << calc(r, n) + calc(c, m) << std::endl;
    }
    else if (r[0] % n == 0) {
        std::cout << "row " << calc(r, n) << std::endl;
    }
    else if (c[0] % m == 0) {
        std::cout << "column " << calc(c, m) << std::endl;
    }
    else {
        std::cout << "impossible" << std::endl;
    }
    
    return 0;
}