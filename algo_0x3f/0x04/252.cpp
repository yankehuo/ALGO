#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 1e4 + 10, M = 2 * N;
int n, k;
int a[N], d[N], b[N];
int acnt;
int cnt[N];
// graph
int h[N], e[M], ne[M], w[M];
int idx;
int sz[N];
int root;
//
int res;
int v[N];
int ans; // rest of nodes (gravity center)

void init() {
    idx = 0;
    memset(h, -1, sizeof(h));
}

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool cmp(int x, int y) {
    return d[x] < d[y];
}

void dfs_find(int sum, int u, int fa) {
    // v[u] = 1;
    sz[u] = 1;
    int max_part = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j] || j == fa) continue;
        dfs_find(sum, j, u);
        max_part = std::max(max_part, sz[j]);
        sz[u] += sz[j];
    }
    max_part = std::max(max_part, sum - sz[u]);
    if (max_part < ans) {
        ans = max_part;
        root = u;
    }
}

void dfs(int u, int fa) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j] || j == fa) continue;
        b[j] = b[u];
        a[++acnt] = j;
        ++cnt[b[j]];
        d[j] = d[u] + w[i];
        dfs(j, u);
    }
}

// sum: cur number of nodes
void calc(int sum, int u, int fa) {
    ans = sum;
    dfs_find(sum, u, fa);
    memset(d, 0, sizeof(d));
    memset(cnt, 0, sizeof(cnt));

    acnt = 0;
    b[root] = root; // belong to sub tree
    a[++acnt] = root;
    v[root] = 1;
    ++cnt[root];

    for (int i = h[root]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j] || j == fa) continue;
        b[j] = j;
        a[++acnt] = j;
        ++cnt[j];
        d[j] = w[i];
        dfs(j, root); // find and add nodes into b[], a[], cnt[], d[]
    }

    std::sort(a + 1, a + acnt + 1, cmp);

    int l = 1, r = acnt;
    while (l < r) {
        --cnt[b[a[l]]];
        while (d[a[l]] + d[a[r]] > k) {
            --cnt[b[a[r]]];
            --r;
        }
        res += r - l - cnt[b[a[l]]]; // exculde the same side
        ++l;
    }

    for (int i = h[root]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j]) continue;
        calc(sz[j], j, root);
    }
}

int main() {
    while (std::cin >> n >> k, n && k) {
        init();
        int x, y, z;
        for (int i = 0; i < n - 1; ++i) {
            std::cin >> x >> y >> z;
            add(x, y, z);
            add(y, x, z);
        }

        memset(v, 0, sizeof(v));
        res = 0;
        calc(n, 1, -1);
        printf("%d\n", res);
    }

    return 0;
}

