#include <iostream>
#include <algorithm>
#include <cstring>


const int N = 1e5 + 10;
struct Node {
    double x, y1, y2;
    int k;
    bool operator<(const Node &rhs) {
        return x < rhs.x;
    }
} node[2 * N];

struct Tree {
    int l, r;
    int cnt;
    double len;
} tr[N * 8];
int left(int u) {
    return u << 1;
}
int right(int u) {
    return u << 1 | 1;
}
int n;
int m;
double raw[N * 2];
int find(double x) {
    return std::lower_bound(raw + 1, raw + m + 1, x) - raw;
}

void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(left(u), l, mid);
    build(right(u), mid + 1, r);
}

void pushup(int u) {
    tr[u].len = tr[u].cnt ? raw[tr[u].r + 1] - raw[tr[u].l] : tr[right(u)].len + tr[left(u)].len;
}

void change(int u, int l, int r, int k) {
    if (l <= tr[u].l && r >= tr[u].r) {
        tr[u].cnt += k;
        pushup(u);
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) change(left(u), l, r, k);
    if (r > mid) change(right(u), l, r, k);
    pushup(u);
}

int main() {
    int tot = 0;
    while (std::cin >> n, n) {
        double x1, y1, x2, y2;
        for (int i = 1; i <= n; ++i) {
            std::cin >> x1 >> y1 >> x2 >> y2;
            node[i] = {x1, y1, y2, 1};
            node[i + n] = {x2, y1, y2, -1};
            raw[i] = y1;
            raw[i + n] = y2;
        }
        n *= 2;
        std::sort(node + 1, node + n + 1);
        std::sort(raw + 1, raw + n + 1);
        m = std::unique(raw + 1, raw + n + 1) - raw - 1;
        double ans = 0;
        build(1, 1, n - 1);
        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                ans += tr[1].len * (node[i].x - node[i - 1].x);
            }
            change(1, find(node[i].y1), find(node[i].y2) - 1, node[i].k);
        }
        printf("Test case #%d\n", ++tot);
        printf("Total explored area: %.2lf\n\n", ans);
    }

    return 0;
}