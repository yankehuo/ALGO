#include <iostream>
#include <cstring>
#include <algorithm>

using LL = long long;
const int N = 5e4 + 10;
int primes[N], idx;
int v[N];
int mobius[N], sum[N];
int t;
int a, b, d;

void init(int n) {
    mobius[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) {
            primes[idx++] = i;
            mobius[i] = -1;
        }
        for (int j = 0; primes[j] <= n / i; ++j) {
            int t = primes[j] * i;
            v[t] = 1;
            if (i % primes[j] == 0) {
                mobius[t] = 0;
                break;
            }
            mobius[t] = mobius[i] * -1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + mobius[i];
    }
}

int main() {
    init(N - 1);
    std::cin >> t;
    while (t--) {
        std::cin >> a >> b >> d;
        a /= d, b /= d;
        int n = std::min(a, b);
        LL res = 0;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = std::min(n, std::min(a / (a / l), b / (b / l)));
            res += (sum[r] - sum[l - 1]) * (LL)(a / l) * (b / l);
        }
        std::cout << res << std::endl;
    }
    return 0;
}