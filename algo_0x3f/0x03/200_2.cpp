#include <iostream>
#include <cstring>

const int N = 5e4 + 10;
int primes[N];
int idx;
int v[N];
int res;
int a, b, c, d;

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

int how(int x, int p) {
    int ans = 0;
    while (x % p == 0) {
        ++ans;
        x /= p;
    }
    return ans;
}

void calc(int p) {
    int ma = how(a, p), mb = how(b, p), mc = how(c, p), md = how(d, p);
    if ((ma > mc && mb < md && mc == md) || (ma > mc && mb == md && mc <= md) || (ma == mc && mb < md && mc <= md)) {
        res *= 1;
        return;
    }
    if (ma == mc && mb == md && mc <= md) {
        res *= md - mc + 1;
        return;
    }
    res = 0;
}

int main() {
    int n;
    std::cin >> n;
    get_primes(50000);
    // gcd(x, a) = c, lcm(x, b) = d
    while (n--) {
        std::cin >> a >> c >> b >> d;
        res = !(d % c);
        for (int i = 0; i < idx; ++i) {
            int p = primes[i];
            if (d % p == 0) {
                calc(p);
                while (d % p == 0) d /= p;
            }
        }
        if (d > 1) {
            calc(d);
        }
        printf("%d\n", res);
    }
    return 0;
}