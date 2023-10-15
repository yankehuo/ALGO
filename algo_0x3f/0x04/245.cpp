#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 5e5 + 10, INF = 0x3f3f3f3f;
int n, m;
int a[N];
struct T {
    int l, r, s, lx, rx, ans;
} t[4 * N];

void pushup(int p) {
    t[p].s = t[p << 1].s + t[p << 1 | 1].s;
    t[p].lx = std::max(t[p << 1].lx, t[p << 1].s + t[p << 1 | 1].lx);
    t[p].rx = std::max(t[p << 1 | 1].rx, t[p << 1 | 1].s + t[p << 1].rx);
    t[p].ans = std::max(std::max(t[p << 1].ans, t[p << 1 | 1].ans), t[p << 1].rx + t[p << 1].lx);

}

void build(int p, int l, int r) {
    t[p].l = l; 
    t[p].r = r;
    if (l == r) {
        t[p].s = t[p].lx = t[p].rx = t[p].ans = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change(int p, int x, int y) {
    if (t[p].l == t[p].r) {
        t[p].s = t[p].lx = t[p].rx = t[p].ans = y;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if (x <= mid) change(p << 1, x, y);
    else change(p << 1 | 1, x, y);
    pushup(p);
}

T ask(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p];
    T a, b, ans;
    a.s = a.lx = a.rx = a.ans = b.s = b.lx = b.rx = b.ans = -INF;
    ans.s = 0;
    int mid = t[p].l + t[p].r >> 1;
    if (l <= mid) {
        a = ask(p << 1, l, r);
        ans.s += a.s;
    }
    if (r > mid) {
        b = ask(p << 1 | 1, l, r);
        ans.s += b.s;
    }
    ans.ans = std::max(std::max(a.ans, b.ans), a.rx + b.lx);
    ans.lx = std::max(a.lx, a.s + b.lx);
    ans.rx = std::max(b.rx, b.s + a.rx);
    if (l > mid) ans.lx = std::max(ans.lx, b.lx);
    if (r <= mid) ans.rx = std::max(ans.rx, a.rx);
    return ans;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    build(1, 1, n);
    while(m--) {
        int op, x, y;
        std::cin >> op >> x >> y;
        if (op == 1) {
            if (x > y) std::swap(x, y);
            std::cout << ask(1, x, y).ans << std::endl;
        }
        else {
            change(1, x, y);
        }
    }

    return 0;
}