#include <iostream>
#include <vector>

std::vector<int> ans, stk;
int remain = 20, n = 0;

void dfs(int u) {
    if (!remain) {
        return;
    }
    if (ans.size() == n) {
        --remain;
        for (auto &p : ans) {
            std::cout << p << " "; 
        }
        std::cout << std::endl;
        return;
    }
    if (stk.size()) {
        ans.push_back(stk.back());
        stk.pop_back();
        dfs(u);
        stk.push_back(ans.back());
        ans.pop_back();
    }
    if (u < n) {
        stk.push_back(u + 1);
        dfs(u + 1);
        stk.pop_back();
    }
}

int main() {
    std::cin >> n;
    dfs(0);
    return 0;
}