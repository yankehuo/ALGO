#include <iostream>

int n;

void dfs(int u, int state) {
    if (u == n) {
        for (int i = 0; i < n; ++i) {
            if (state >> i & 1) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
        return;
    }
    dfs(u + 1, state | 1 << u);
    dfs(u + 1, state);
}

int main() {
    std::cin >> n;
    dfs(0, 0);

    return 0;
}