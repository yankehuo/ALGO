#include <iostream>
int n;
const int N = 1e5 + 10;
int primes[N];
int v[N];
int cnt = 0;

int main() {
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}