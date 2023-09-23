#include <iostream>
#include <cstring>
#include <algorithm>

using LL = long long;
const int N = 2e5 + 10;
int a[N], t[N];
int lower[N], greater[N];
int n;

int lowbit(int x) {
    return x & -x;
}

int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) {
        res += t[x];
    }
    return res;
}

void add(int x, int y) {
    for (; x <= n; x += lowbit(x)) {
        t[x] += y;
    }
}

void calc() {
    LL res0 = 0;
    LL res1 = 0;
    for (int i = 1; i <= n; ++i) {
        int y = a[i];
        lower[i] = ask(y - 1);
        res1 += (LL)lower[i] * (y - 1 - lower[i]);
        greater[i] = ask(n) - ask(y);
        res0 += (LL)greater[i] * (n - y - greater[i]);
        add(y, 1);
    }
    printf("%lld %lld\n", res0, res1);
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    calc();
    return 0;
}
