#include <iostream>
#include <queue>
#include <algorithm>

int n;

int main() {
    std::cin >> n;
    std::priority_queue<int, std::vector<int>, std::greater<>> hp;
    int x;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        hp.push(x);
    }
    int res = 0;
    while (hp.size() > 1) {
        int t1 = hp.top();
        hp.pop();
        int t2 = hp.top();
        hp.pop();
        res += t1 + t2;
        hp.push(t1 + t2);
    }
    std::cout << res << std::endl;
    return 0;
}