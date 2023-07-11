#include <iostream>
#include <algorithm>

const int N = 22;
int n, w;
int cab[N], c[N];
int res, cnt, u;

// how to distribute u-th cat in cnt cabs
void dfs(int u, int cnt) {
    if (cnt >= res) return;
    if (u == n + 1) {
        res = std::min(res, cnt);
        return;
    }
    for (int i = 1; i <= cnt; ++i) {
        if (cab[i] + c[u] <= w) {
            cab[i] += c[u];
            dfs(u + 1, cnt);
            cab[i] -= c[u];
        }
    }
    cab[cnt + 1] = c[u];
    dfs(u + 1, cnt + 1);
    cab[cnt + 1] = 0;
}

int main() {
    std::cin >> n >> w;
    for (int i = 1; i <= n; ++i) {
        std::cin >> c[i];
    }
    std::sort(c + 1, c + n + 1, std::greater<int>());
    res = n;
    dfs(1, 0);
    std::cout << res << std::endl;

    return 0;
}