#include <iostream>

const int N = 1e3 + 10;
int primes[N];
int phi[N];
int v[N];
int idx;
int n, c;

void euler(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) {
            primes[idx++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

int get_sum(int n) {
    int res = 0;
    for (int i = 2; i <= n; ++i) {
        res += phi[i];
    }
    return res;
}

int main() {
    std::cin >> c;
    euler(1000);
    phi[1] = 1;
    int cnt = 0;
    while (c--) {
        std::cin >> n;
        int res = get_sum(n) * 2 + 3;
        printf("%d %d %d\n", ++cnt, n, res);
    }
    return 0;
}