#include <iostream>
#include <cstring>
#include <cmath>

const int N = 1e5 + 10;
const int MOD = 1e9 + 9; // prime
using LL = long long;
int p[N];
LL fac[N];
int v[N];

int qmi(int a, int b, int p) {
    int res = 1;
    a %= p;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = (long long)res * a % p;
        }
        a = (long long)a * a % p;
    }
    return res;
}

int main() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i <= 100000; ++i) {
        fac[i] = fac[i - 1] * i % MOD;
        // printf("%lld ", fac[i]);
    }
    // puts("");
    int T;
    int n;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            std::cin >> p[i];
            v[i] = 0;
        }
        // memset(v, 0, sizeof(v));
        int k = 0;
        LL res = 1;
        for (int i = 1; i <= n; ++i) {
            if (v[i]) continue;
            int len = 1;
            v[i] = 1;
            for (int j = p[i]; j != i; j = p[j]) {
                ++len;
                v[j] = 1;
            }
            res = res * (len == 1 ? 1 : qmi(len, len - 2, MOD)) % MOD;
            res = res * qmi(fac[len - 1], MOD - 2, MOD) % MOD;
            ++k;
        }
        res = res * fac[n - k] % MOD; 
        printf("%lld\n", res);
    }
    return 0;
}