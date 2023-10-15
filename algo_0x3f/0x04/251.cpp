#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using LL = long long;
using PLL = std::pair<LL, LL>;
const int N = 5e4 + 10;
struct Node {
    int id, l, r;
} p[N];
int cnt[N];
int a[N];
int L[N], R[N];
int n, m;
LL ans; // C(cnt[x], 2)
PLL res[N];

bool cmp0(Node &a, Node &b) {
    return a.l < b.l;
}

bool cmp1(Node &a, Node &b) {
    return a.r < b.r;
}

void work(int x, int w) { // color:x, cnt:w; C(cnt[x], 2)
    ans -= (LL)cnt[x] * (cnt[x] - 1) / 2;
    cnt[x] += w;
    ans += (LL)cnt[x] * (cnt[x] - 1) / 2;
}

LL C(int x) { // C(x, 2)
    return (LL)x * (x - 1) / 2;
}

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> p[i].l >> p[i].r;
        p[i].id = i;
    }
    std::sort(p + 1, p + 1 + m, cmp0);
    int t = sqrt(m);
    // int len = n / t;
    int len = sqrt(m);
    for (int i = 1; i <= t; ++i) {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
        std::sort(p + L[i], p + R[i] + 1, cmp1);
    }
    if (R[t] < m) {
        ++t;
        L[t] = R[t - 1] + 1;
        R[t] = m;
        std::sort(p + L[t], p + R[t] + 1, cmp1);
    }
    for (int i = 1; i <= t; ++i) {
        memset(cnt, 0, sizeof(cnt));
        ans = 0;
        // first get answer of [l, r], then add or subtract
        int l = p[L[i]].l, r = p[L[i]].r;
        for (int j = l; j <= r; ++j) {
            work(a[j], 1);
        }
        res[p[L[i]].id] = {ans, C(r - l + 1)};

        for (int j = L[i] + 1; j <= R[i]; ++j) {
            while (r < p[j].r) work(a[++r], 1);
            while (r > p[j].r) work(a[r--], -1);
            while (l < p[j].l) work(a[l++], -1);
            while (l > p[j].l) work(a[--l], 1);
            if (p[j].l == p[j].r) {
                res[p[j].id] = {0, 1};
            }
            else {
                res[p[j].id] = {ans, C(p[j].r - p[j].l + 1)};
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        LL a = res[i].first, b = res[i].second;
        LL d = gcd(a, b);
        if (!d) {
            b = 1;
        }
        else {
            a /= d;
            b /= d;
        }
        printf("%lld/%lld\n", a, b);
    }

    return 0;
}