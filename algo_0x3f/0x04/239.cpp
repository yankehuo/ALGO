#include <iostream>
#include <algorithm>
#include <cstring>

// l r 5000*2
const int M = 10010;
int a[M];
struct {
    int l, r, st;
} query[M];
int fa[M], d[M];
int n, m;
int idx = 0;

void discrete() {
    std::cin >> n >> m;
    int l, r;
    char st[5];
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %s", &query[i].l, &query[i].r, st);
        query[i].st = st[0] == 'e' ? 0 : 1;
        a[++idx] = query[i].l - 1;
        a[++idx] = query[i].r;
    }
    std::sort(a + 1, a + idx + 1);
    n = std::unique(a + 1, a + idx + 1) - (a + 1);
}

int get(int x) {
    if (x == fa[x]) return x;
    int u = get(fa[x]);
    d[x] ^= d[fa[x]];
    return fa[x] = u;
}

int main() {
    discrete();
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    bool flag = 1;
    for (int i = 1; i <= m; ++i) {
        int x = std::lower_bound(a + 1, a + n + 1, query[i].l - 1) - a;
        int y = std::lower_bound(a + 1, a + n + 1, query[i].r) - a;
        int u = get(x), v = get(y);
        if (u == v) {
            // d[x] ^ d[y]
            if ((d[x] ^ d[y]) != query[i].st) {
                printf("%d\n", i - 1);
                flag = 0;
                break;
            }
        }
        else {
            fa[u] = v;
            d[u] = query[i].st ^ d[x] ^ d[y];
        }
    }
    if (flag) {
        printf("%d\n", m);
    }

    return 0;
}


/*
int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}

int main() {
    discrete();
    for (int i = 1; i <= 2 * n; ++i) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        int x = std::lower_bound(a + 1, a + n + 1, query[i].l - 1) - (a + 1);
        int y = std::lower_bound(a + 1, a + n + 1, query[i].r) - (a + 1);
        int x_odd = x, x_even = x + n;
        int y_odd = y, y_even = y + n;
        if (query[i].st == 0) { // even
            if (get(x_odd) == get(y_even)) {
                printf("%d\n", i - 1);
                return 0;
            }
            fa[get(x_odd)] = get(y_odd);
            fa[get(x_even)] = get(y_even);
        }
        else { // odd
            if (get(x_odd) == get(y_odd)) {
                printf("%d\n", i - 1);
                return 0;
            }
            fa[get(x_odd)] = get(y_even);
            fa[get(x_even)] = get(y_odd);
        }
    }
    printf("%d\n", m);
    return 0;
}





*/