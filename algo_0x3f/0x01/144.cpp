#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 10, M = 2e5 + 10, SZ = 31e5 + 10;
int h[N], e[M], ne[M], w[M], cnt;
int trie[SZ][2], idx;
int arr[N], n;

void add(int a, int b, int c) {
    e[cnt] = b, w[cnt] = c, ne[cnt] = h[a], h[a] = cnt++;
}

void dfs(int p, int u, int sum) {
    arr[u] = sum;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j != p) dfs(u, j, sum ^ w[i]);
    }
}

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (!trie[p][u]) trie[p][u] = ++idx;
        p = trie[p][u];
    }
}

int query(int x) {
    int p = 0;
    int res = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (trie[p][!u]) res |= 1 << i, p = trie[p][!u];
        else p = trie[p][u];
    }
    return res;
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    int a, b, c;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    dfs(-1, 0, 0);
    for (int i = 0; i < n; ++i) insert(arr[i]);
    int res = 0;
    for (int i = 0; i < n; ++i) res = std::max(res, query(arr[i]));
    printf("%d\n", res);

    return 0;
}