#include <iostream>
#include <algorithm>
#include <queue>

int n, k;
using PLI = std::pair<long long, int>;

int main() {
    std::cin >> n >> k;
    std::priority_queue<PLI, std::vector<PLI>, std::greater<>> hp;
    long long x;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        hp.push({x, 0});
    }
    while ((n - 1) % (k - 1)) {
        hp.push({0, 0});
        ++n;
    }
    long long res = 0;
    int idx = 0;
    while (hp.size() > 1) {
        long long val = 0;
        int depth = 0;
        for (int i = 0; i < k; ++i) {
            val += hp.top().first;
            depth = std::max(depth, hp.top().second);
            hp.pop();
            ++idx;
            std::cout << "idx:" << idx << std::endl;
        }
        res += val;
        hp.push({val, depth + 1});
    }
    std::cout << res << "\n" << hp.top().second << std::endl;

    return 0;
}