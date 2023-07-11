#include <iostream>
#include <cstring>

const int N = 1e6 + 10;
int v[N];
int primes[N];
int n;
int idx;

void get_primes(int n) {
    memset(v, 0, sizeof(v));
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) primes[idx++] = i;
        for (int j = primes[i]; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    std::cin >> n;
    get_primes(n);
    for (int i = 0; i < idx; ++i) {
        int p = primes[i];
        int cnt = 0;
        for (int j = n; j; j /= p) {
            cnt += j / p;
        }
        std::cout << p << ' ' << cnt << std::endl;
    }
    return 0;
}