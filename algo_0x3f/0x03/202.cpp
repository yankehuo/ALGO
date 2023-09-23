#include <iostream>
#include <cstring>

// const int N = 2e9 + 10;
// int primes[N];
// int euler[N];
// int v[N];
// int cnt = 0;
using LL = long long;
// 9L/d | 10^x-1
// 10^x===1(mod 9L/d)
// a^x===1, x0

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

LL qmul(LL a, LL b, LL p) {
    LL res = 0;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = (res + a) % p;
        }
        a = (a + a) % p;
    }
    return res;
}

LL qmi(LL a, LL b, LL p) {
    LL res = 1;
    a %= p;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = qmul(res, a, p);
        }
        a = qmul(a, a, p);
    }
    return res;
}

// void get_euler(int n) {
//     for (int i = 2; i <= n; ++i) {
//         if (!v[i]) {
//             primes[cnt++] = i;
//             euler[i] = i - 1;
//         }
//         for (int j = 0; primes[j] <= n / i; ++j) {
//             v[primes[j] * i] = 1;
//             if (i % primes[j] == 0) {
//                 euler[i * primes[j]] = euler[i] * primes[j];
//                 break;
//             }
//             euler[i * primes[j]] = euler[i] * (primes[j] - 1);
//         }
//     }
// }

LL euler(LL c) {
    LL res = c;
    for (int i = 2; i <= c / i; ++i) {
        if (c % i == 0) {
            while (c % i == 0) c /= i;
            // res = res * (i - 1) / i;
            // note
            res = res / i * (i - 1);
        }
    }
    // if (c > 1) res = res * (c - 1) / c;
    if (c > 1) res = res / c * (c - 1);
    return res;
}

int main() {
    LL L;
    int idx = 0;
    // get_euler(2e9);
    while (std::cin >> L, L) {
        LL d = gcd(L, 8);
        LL c = 9 * L / d;
        LL phi = euler(c);
        LL res = 1e18;
        if (c % 2 == 0 || c % 5 == 0) res = 0;
        else {
            for (LL i = 1; i <= phi / i; ++i) {
                if (phi % i == 0) {
                    if (qmi(10, i, c) == 1) res = std::min(res, i);
                    if (qmi(10, phi / i, c) == 1) res = std::min(res, phi / i);
                }
            }
        }
        printf("Case %d: %lld\n", ++idx, res);
    }
    return 0;
}