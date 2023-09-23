#include <iostream>
#include <cstring>

const int N = 5e4 + 10;
int primes[N];
int idx;
int v[N];
using PII = std::pair<int, int>;
PII factor[N];
int cntf;
int divisor[N], cntd;

void get_primes(int n) {
    memset(v, 0, sizeof(v));
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) primes[idx++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// 约数
void dfs(int u, int p) {
    if (u == cntf) {
        divisor[cntd++] = p;
        return;
    }
    for (int i = 0; i <= factor[u].second; ++i) {
        dfs(u + 1, p);
        p *= factor[u].first;
    }
}

// gcd(x, a0)=a1, lcm(x, b0) = b1
int main() {
    int n;
    std::cin >> n;
    get_primes(50000);
    int a0, a1, b0, b1;
    while (n--) {
        std::cin >> a0 >> a1 >> b0 >> b1;
        cntf = 0;
        int d = b1;
        for (int i = 0; primes[i] <= d / primes[i]; ++i) {
            int p = primes[i];
            if (d % p == 0) {
                int s = 0;
                while (d % p == 0) ++s, d /= p;
                factor[cntf++] = {p, s};
            }
        }
        if (d > 1) {
            factor[cntf++] = {d, 1};
        }
        // 拼凑约数
        cntd = 0;
        dfs(0, 1);
        int res = 0;
        for (int i = 0; i < cntd; ++i) {
            int x = divisor[i];
            std::cout << "divisor:" << x << " ";
            printf("=============\n");
            if (gcd(x, a0) == a1 && (long long)x * b0 / gcd(x, b0) == b1) ++res;
        }
        std::cout << res << std::endl;
    }

    return 0;
}