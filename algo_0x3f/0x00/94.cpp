#include <iostream>
#include <vector>

int n;
std::vector<int> arr;

void dfs(int u, int state) {
    if (u == n) {
        for (auto &p : arr) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (state >> i & 1) {
            continue;
        }
        arr.emplace_back(i + 1);
        dfs(u + 1, state | 1 << i);
        arr.pop_back();
    }
}

int main() {
    std::cin >> n;
    dfs(0, 0);

    return 0;
}