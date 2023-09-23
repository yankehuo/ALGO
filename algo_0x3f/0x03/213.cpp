#include <iostream>
#include <cstring>

using LL = long long;
const int MOD = 999911659;
const int N = 36000;
int fac[N]; // !
int p[4] = {2, 3, 4679, 35617};
int a[4]; // % 2 3 4679 35617
int n, q;

int qmi(int a, int b, int p) {
    int res = 1;
    a %= p;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = (LL)res * a % p;
        }
        a = (LL)a * a % p;
    }
    return res;
}

int extgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int inv(int a, int p) {
    int x, y;
    extgcd(a, p, x, y);
    return (x % p + p) % p;
}

int C(int a, int b, int p) {
    if (b > a) return 0;
    return (LL)fac[a] * inv(fac[b], p) % p * inv(fac[a - b], p) % p;
}

// C(a, b) % p
int lucas(int a, int b, int p) {
    if (a < p && b < p) {
        return C(a, b, p);
    }
    return (LL)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}

int main() {
    std::cin >> n >> q;
    q %= MOD;
    if (!q) {
        puts("0");
        return 0;
    }

    fac[0] = 1;
    for (int i = 1; i <= p[3]; ++i) {
        fac[i] = (LL)fac[i - 1] * i % (MOD - 1);
    }
    // lucas % 2
    for (int i = 1; i <= n / i; ++i) {
        if (n % i == 0) {
            for (int j = 0; j < 4; ++j) {
                a[j] = (a[j] + lucas(n, i, p[j])) % p[j];
            }
            if (i * i != n) {
                for (int j = 0; j < 4; ++j) {
                    a[j] = (a[j] + lucas(n, n / i, p[j])) % p[j];
                }
            }
        }
    }
    // x = sum{a[i] * M[i] * t[i]}
    // M[i]t[i]==1(%m[i])
    // M[i] = (MOD - 1) / p[i]
    int x = 0;
    for (int i = 0; i < 4; ++i) {
        int M = (MOD - 1) / p[i];
        int t, y;
        extgcd(M, p[i], t, y);
        x = (x + (LL)a[i] * M % (MOD - 1) * t % (MOD - 1)) % (MOD - 1);
    }
    x = (x + (MOD - 1)) % (MOD - 1);
    int res = qmi(q, x, MOD);
    printf("%d\n", res);

    return 0;
}