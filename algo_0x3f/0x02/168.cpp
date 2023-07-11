#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>

const int N = 22;
int a[N];
int minv[N], mins[N];
int H[N], R[N];
int n, m;
int res = INT_MAX;

void dfs(int u, int s, int v) {
    if (v + minv[u] > n) return;
    if (s + mins[u] >= res) return;
    if (s + 2 * (n - v) / R[u + 1] >= res) return;
    if (!u) {
        if (v == n) res = s;
        return;
    }
    for (int r = std::min((int)sqrt(n - v), R[u + 1] - 1); r >= u; --r) {
        for (int h = std::min((n - v) / r / r, H[u + 1] - 1); h >= u; --h) {
            R[u] = r, H[u] = h;
            int t = u == m ? r * r : 0;
            dfs(u - 1, s + 2 * r * h + t, v + r * r * h);
        }
    }
}

int main() {
    std::cin >> n >> m;
    // preprocess min s and v
    for (int i = 1; i <= m; ++i) {
        mins[i] = mins[i - 1] + 2 * i * i;
        minv[i] = minv[i - 1] + i * i * i;
    }
    H[m + 1] = R[m + 1] = INT_MAX;
    dfs(m, 0, 0);
    if (res == INT_MAX) res = 0;
    std::cout << res << std::endl;
    return 0;
}