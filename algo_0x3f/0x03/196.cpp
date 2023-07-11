#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 5e4 + 10;
int primes[N];
int v[N];
int idx = 0;

void get_prime(int n) {
    memset(v, 0, sizeof(v));
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) primes[idx++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    long long l, r;
    while (std::cin >> l >> r) {
        get_prime(50000);
        memset(v, 0, sizeof(v));
        for (int i = 0; i < idx; ++i) {
            int p = primes[i];
            for (long long j = std::max(2ll * p, (l + p - 1) / p * p); j <= r; j += p) {
                v[j - l] = 1;
            }
        }
        idx = 0;
        for (int i = 0; i <= r - l; ++i) {
            if (!v[i] && i + l > 1) {
                primes[idx++] = i + l;
            }
        }
        if (idx < 2) puts("There are no adjacent primes.");
        else {
            int minp = 0, maxp = 0;
            for (int i = 0; i < idx - 1; ++i) {
                int dis = primes[i + 1] - primes[i];
                if (dis < primes[minp + 1] - primes[minp]) {
                    minp = i;
                }
                if (dis > primes[maxp + 1] - primes[maxp]) {
                    maxp = i;
                }
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", primes[minp], primes[minp + 1], primes[maxp], primes[maxp + 1]);
        }
    }
    return 0;
}