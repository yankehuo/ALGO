#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using std::vector;
using PII = std::pair<int, int>;
std::vector<PII> arr;
int n;

int main() {
    while (scanf("%d", &n) != EOF) {
        int p, d;
        for (int i = 0; i < n; ++i) {
            std::cin >> p >> d;
            arr.emplace_back(d, p);
        }
        std::sort(arr.begin(), arr.end());
        std::priority_queue<int, vector<int>, std::greater<int>> hp;
        for (auto &p : arr) {
            hp.push(p.second);
            if (hp.size() > p.first) hp.pop();
        }
        int res = 0;
        while (hp.size()) {
            res += hp.top();
            hp.pop();
        }
        std::cout << res << std::endl;
        arr.clear();
    }
    return 0;
}