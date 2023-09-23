#include <iostream>
#include <cstring>
#include <cmath>

const int M = 10007;
const int N = 1010;
using LL = long long;
LL inv[N];
LL x, y;

LL extgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1; 
        y = 0;
        return a;
    }
    LL d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

LL qmi(LL a, LL b, LL p) {
    a %= p;
    LL res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
    }
    return res;
}

int main() {
    // pre process
    for (int i = 1; i <= 1000; ++i) {
        extgcd(i, M, x, y);
        inv[i] = (x % M + M) % M;
    }

    LL a, b, k, n, m;
    std::cin >> a >> b >> k >> n >> m;
    LL res = qmi(a, n, M) * qmi(b, k - n, M) % M;
    for (int i = 1, j = k; i <= n; ++i, --j) {
        res = res * inv[i] % M * j % M;
    }
    printf("%lld\n", res);

    return 0;
}