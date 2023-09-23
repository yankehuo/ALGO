#include <iostream>
#include <cstring>
#include <algorithm>

using LL = long long;
const int MOD = 1e9 + 7;
const int N = 26;
LL a[N];
LL inv[N];
LL n, m;

LL qmi(LL a, LL b, LL p) {
    LL res = 1;
    a %= p;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
    }
    return res;
}

LL C(LL y, LL x) {
    if (y < 0 || x < 0 || y < x) return 0;
    y %= MOD;
    if (y == 0 || x == 0) return 1;
    LL res = 1;
    for (int i = 0; i < x; ++i) {
        res = res * (y - i) % MOD;
    }
    for (int i = 1; i <= x; ++i) {
        res = res * inv[i] % MOD;
    }
    return res;
}

int main() {
    for (int i = 1; i <= 20; ++i) {
        inv[i] = qmi(i, MOD - 2, MOD);
    }
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    LL res = C(n + m - 1, n - 1);
    for (int x = 1; x < (1 << n); ++x) {
        LL t = n + m;
        LL p = 0;
        for (int i = 0; i < n; ++i) {
            if (x >> i & 1) {
                ++p;
                t -= a[i + 1];
            }
        }
        t -= p + 1;
        if (p & 1) {
            res = (res - C(t, n - 1)) % MOD;
        }
        else {
            res = (res + C(t, n - 1)) % MOD;
        }
    }
    std::cout << (res + MOD) % MOD << std::endl;

    return 0;
}