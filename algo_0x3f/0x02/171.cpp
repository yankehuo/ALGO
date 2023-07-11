#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 48;
int n, w;
int g[N], wt[1 << 24];
int k;
int cnt, res;
using LL = long long;

void dfs(int u, int s) {
    if (u == k) {
        wt[cnt++] = s;
        return;
    }
    if ((LL)s + g[u] <= w) dfs(u + 1, s + g[u]);
    dfs(u + 1, s);
}

void dfs2(int u, int s) {
    if (u == n) {
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if ((LL)wt[mid] + s <= w) l = mid;
            else r = mid - 1;
        }
        if ((LL)wt[l] + s <= w) res = std::max(res, wt[l] + s);
        return;
    }
    if ((LL)s + g[u] <= w) dfs2(u + 1, s + g[u]);
    dfs2(u + 1, s);
}

int main() {
    std::cin >> w >> n;
    for (int i = 0; i < n; ++i) std::cin >> g[i];
    std::sort(g, g + n, std::greater<int>());
    k = n >> 1;
    dfs(0, 0);
    std::sort(wt, wt + cnt);
    cnt = std::unique(wt, wt + cnt) - wt;
    dfs2(k, 0);
    std::cout << res << std::endl;

    return 0;
}