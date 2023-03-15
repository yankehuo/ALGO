#include <iostream>
#include <queue>
#include <vector>

int p, m, n;

int main() {
    std::cin >> p;
    int x;
    while (p--) {
        // max
        std::priority_queue<int, std::vector<int>> hp1; 
        // min
        std::priority_queue<int, std::vector<int>, std::greater<int>> hp2; 
        std::cin >> n >> m;
        std::cout << n << " " << (m + 1) / 2 << std::endl;
        int cnt = 0;
        for (int i = 0; i < m; ++i) {
            std::cin >> x;
            if (hp1.size() == 0 || x <= hp1.top()) {
                hp1.push(x);
            }
            else {
                hp2.push(x);
            }
            if (hp2.size() > hp1.size()) {
                hp1.push(hp2.top());
                hp2.pop();
            }
            if (hp1.size() - hp2.size() == 2) {
                hp2.push(hp1.top());
                hp1.pop();
            }
            if ((i & 1) == 0) {
                std::cout << hp1.top() << " ";
                if (++cnt % 10 == 0) {
                    std::cout << std::endl;
                }
            }
        }
        if (cnt % 10) {
            std::cout << std::endl;
        }
    }
    return 0;
}