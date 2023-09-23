#include <iostream>
#include <cstring>
#include <algorithm>

// sumi(1, x)sumj(1, i)b[j] = sumi(1, x)(x -i + 1)b[i] = (x+1)sumi(1,x)b[i] - sumi(1,x)ib[i]
// 增量：sum(1,x)b[i] sum(1,x)i*b[i] add:d add:i*d
using LL = long long;
const int N = 1e5 + 10;
int a[N];
LL c[2][N], sum[N];
int n, m;

int lowbit(int x) {
    return x & -x;
}

LL ask(int k, int x) {
    LL res = 0;
    for (; x; x -= lowbit(x)) {
        res += c[k][x];
    }
    return res;
}

void add(int k, int x, int y) {
    for (; x <= n; x += lowbit(x)) {
        c[k][x] += y;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    char op;
    int l, r, d;
    while (m--) {
        std::cin >> op;
        if (op == 'C') {
            std::cin >> l >> r >> d;
            add(0, l, d);
            add(0, r + 1, -d);
            add(1, l, l * d);
            add(1, r + 1, -(r + 1) * d);
        }
        else {
            std::cin >> l >> r;
            LL res = (sum[r] + (r + 1) * ask(0, r) - ask(1, r)) - (sum[l - 1] + l * ask(0, l - 1) - ask(1, l - 1));
            printf("%lld\n", res);
        }
    }
    return 0;
}
