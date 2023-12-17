#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m;
int tr[N], maxy;
int res[N];
struct Node {
    int x, y, z;
    bool operator<(const Node &rhs) const {
        return x < rhs.x;
    }
};
Node a[N], b[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int y) {
    for (int i = x; i <= maxy; i += lowbit(i)) {
        tr[i] = std::max(tr[i], y);
    }
}

int ask(int x) {
    int res = -INF;
    for (int i = x; i; i -= lowbit(i)) {
        res = std::max(res, tr[i]);
    }
    return res;
}

void calc(int st, int ed, int t, int dx, int dy) {
    for (int i = st; i != ed; i += t) {
        int y;
        y = dy == 1 ? b[i].y : maxy - b[i].y + 1;
        int dist = dx * b[i].x + dy * b[i].y;
        if (a[b[i].z].z == 1) {
            add(y, dist);
        }
        else {
            res[b[i].z] = std::min(res[b[i].z], abs(dist - ask(y)));
        }
    }

    for (int i = st; i != ed; i += t) {
        int y;
        y = dy == 1 ? b[i].y : maxy - b[i].y + 1;
        if (a[b[i].z].z == 1) {
            for (int j = y; j <= maxy; j += lowbit(j)) {
                if (tr[j] == -INF) break;
                tr[j] = -INF;
            }
        }
    }

}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    if (l <= mid) cdq(l, mid);
    if (r > mid) cdq(mid + 1, r);
    if (r > n) {
        int cnt = 0;
        for (int i = l; i <= r; ++i) {
            if ((i <= mid && a[i].z == 1) || (i > mid && a[i].z == 2)) {
                b[++cnt] = a[i];
                b[cnt].z = i;
            }
        }
        std::sort(b + 1, b + cnt + 1); // remove ||
        calc(1, cnt + 1, 1, 1, 1); //x+y
        calc(1, cnt + 1, 1, 1, -1); //x-y
        calc(cnt, 0, -1, -1, 1); //-x+y
        calc(cnt, 0, -1, -1, -1); //-x-y
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i].x >> a[i].y;
        ++a[i].y; // for +1
        a[i].z = 1;
    }
    for (int i = n + 1; i <= n + m; ++i) {
        std::cin >> a[i].z >> a[i].x >> a[i].y;
        ++a[i].y; // for +1
    }
    for (int i = 1; i <= n + m; ++i) {
        maxy = std::max(maxy, a[i].y);
    }
    memset(tr, 0xcf, sizeof(tr));
    memset(res, 0x3f, sizeof(res));
    cdq(1, n + m);
    for (int i = 1; i <= n + m; ++i) {
        if (a[i].z == 2) {
            printf("%d\n", res[i]);
        }
    }

    return 0;
}
