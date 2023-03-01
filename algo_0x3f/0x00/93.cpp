#include <iostream>

int n, m;

void dfs(int u, int state, int cnt) {
    if (u > n || cnt + (n - u + 1) < m) {
        return;
    }
    if (cnt == m) {
        for (int i = 0; i < n; ++i) {
            if (state >> i & 1) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
        return;
    }
    dfs(u + 1, state | 1 << u, cnt + 1);
    dfs(u + 1, state, cnt);
}

int main() {
    std::cin >> n >> m;
    dfs(0, 0, 0);

    return 0;
}