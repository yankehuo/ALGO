#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
long long l, r;
bool v[N];
int cnt;
int primes[N];

void getPrimes(int n) {
    memset(v, 0, sizeof v);
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    while (cin >> l >> r) {
        getPrimes(50000);
        memset(v, 0, sizeof v);
        for (int i = 0; i < cnt; ++i) {
            int p = primes[i];
            for (long long j = max((l + p - 1) / p * p, 2ll * p); j <= r; j += p) {
                v[j - l] = 1;
            }
        }
        cnt = 0;
        for (int i = l; i <= r; ++i) {
            if (!v[i - l] && i > 1) {
                primes[cnt++] = i;
            }
        }
        if (cnt < 2) {
            puts("There are no adjacent primes.");
        }
        else {
            int maxp = 0, minp = 0;
            for (int i = 0; i < cnt - 1; ++i) {
                int d = primes[i + 1] - primes[i];
                if (d < primes[minp + 1] - primes[minp]) {
                    minp = i;
                }
                if (d > primes[maxp + 1] - primes[maxp]) {
                    maxp = i;
                }
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", 
                primes[minp], primes[minp + 1], primes[maxp], primes[maxp + 1]);
        }
    }
    return 0;
}
