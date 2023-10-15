#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using LL = long long;
const int N = 25e4 + 10;
struct Node {
    int x, y, m, p, r;
};
Node p[N];
Node q[N]; // for queue
int hh, tt;
int v[N];
int L[N], R[N], M[N];

LL get_dist(int x, int y) {
    LL dx = x - q[0].x, dy = y - q[0].y;
    return dx * dx + dy * dy;
}

bool cmp0(Node &a, Node &b) {
    return a.m < b.m;
}
bool cmp1(Node &a, Node &b) {
    return get_dist(a.x, a.y) < get_dist(b.x, b.y);
}

int main() {
    int n;
    std::cin >> q[0].x >> q[0].y >> q[0].p >> q[0].r >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i].x >> p[i].y >> p[i].m >> p[i].p >> p[i].r;
    }
    std::sort(p + 1, p + n + 1, cmp0);
    int t = sqrt(n);
    int len = n / t;
    for (int i = 1; i <= t; ++i) {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
        M[i] = p[R[i]].m;
        std::sort(p + L[i], p + R[i] + 1, cmp1);
    }
    if (R[t] < n) {
        ++t;
        L[t] = R[t - 1] + 1;
        R[t] = n;
        M[t] = p[R[t]].m;
        std::sort(p + L[t], p + R[t] + 1, cmp1);
    }

    hh = 0, tt = 0;
    while (hh <= tt) {
        Node qt = q[hh++];
        int k = 0;
        for (int i = 1; i <= t; ++i) {
            if (M[i] <= qt.p) {
                k = i;
            }
            else {
                break;
            }
        }
        for (int i = 1; i <= k; ++i) {
            while (L[i] <= R[i] && get_dist(p[L[i]].x, p[L[i]].y) <= (LL)qt.r * qt.r) {
                if (!v[L[i]]) {
                    v[L[i]] = 1;
                    q[++tt] = p[L[i]];
                }
                ++L[i];
            }
        }
        if (++k <= t) {
            for (int i = L[k]; i <= R[k]; ++i) {
                if (!v[i] && p[i].m <= qt.p && get_dist(p[i].x, p[i].y) <= (LL)qt.r * qt.r) {
                    v[i] = 1;
                    q[++tt] = p[i];
                }
            }
        }
    }
    printf("%d\n", tt);

    return 0;
}