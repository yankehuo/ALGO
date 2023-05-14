#include <iostream>
#include <algorithm>
#include <climits>

const int N = 1e5 + 10, M = 7e6 + 10;
int n, m, q, u, v, t;
int tt1 = -1, tt2 = -1, tt3 = -1;
int hh1 = 0, hh2 = 0, hh3 = 0;
int q1[N], q2[M], q3[M];

int find_max() {
    int res = INT_MIN;
    if (hh1 <= tt1) res = std::max(res, q1[hh1]);
    if (hh2 <= tt2) res = std::max(res, q2[hh2]);
    if (hh3 <= tt3) res = std::max(res, q3[hh3]);
    if (hh1 <= tt1 && res == q1[hh1]) ++hh1;
    else if (hh2 <= tt2 && res == q2[hh2]) ++hh2;
    else ++hh3;
    return res;
}

int main() {
    std::cin >> n >> m >> q >> u >> v >> t;
    for (int i = 0; i < n; ++i) {
        std::cin >> q1[i];
    }
    std::sort(q1, q1 + n, std::greater<int>());
    tt1 = n - 1;
    int delta = 0;
    for (int i = 1; i <= m; ++i) {
        int max_val = find_max();
        max_val += delta;
        if (i % t == 0) {
            printf("%d ", max_val);
        }
        delta += q;
        int left = max_val * 1ll * u / v;
        int right = max_val - left;
        q2[++tt2] = left - delta;
        q3[++tt3] = right -delta;
    }
    puts("");
    for (int i = 1; i <= n + m; ++i) {
        int max_val = find_max();
        if (i % t == 0) {
            printf("%d ", max_val + delta);
        }
    }
    puts("");
    return 0;
}