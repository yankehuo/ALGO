#include <iostream>
#include <math.h>

const int N = 11311;
const int base = 1e9;
int n;
int cnt[N];
long long res[N], tt;
int primes[N], tot;
bool v[120001];

void init() {
    for (int i = 2; i <= 2 * n; ++i) {
        if (!v[i]) {
            primes[++tot] = i;
            for (int j = n * 2 / i; j; j /= i) {
                cnt[tot] += j;
            }
            for (int j = n / i; j; j /= i) {
                cnt[tot] -= j * 2;
            }
            for (int j = n + 1; j % i == 0; j /= i) {
                cnt[tot]--;
            }
        }
        for (int j = 1; primes[j] <= n * 2 / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

void multi(long long *res, int b) {
    long long t = 0;
    for (int i = 0; i <= tt; ++i) {
        t = t + res[i] * b;
        res[i] = t % base;
        // std::cout << res[i] << std::endl;
        t /= base;
    }
    while (t) {
        res[++tt] = t % base;
        // std::cout << res[tt] << std::endl;
        t /= base;
    }
}

void print() {
    printf("%lld", res[tt]);
    for (int i = tt - 1; i >= 0; --i) {
        printf("%09lld", res[i]);
    }
    puts("");
}

int main() {
    std::cin >> n;
    init();
    res[0] = 1;
    for (int i = 1; i <= tot; ++i) {
        if (cnt[i]) {
            multi(res, pow(primes[i], cnt[i]));
        }
    }
    print();

    return 0;
}