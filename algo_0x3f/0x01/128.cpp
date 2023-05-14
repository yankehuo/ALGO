#include <iostream>
#include <vector>
#include <climits>

std::string op;
int q;
const int N = 1e6 + 10;
int s[N], f[N];
std::vector<int> left, right;

int main() {
    std::cin >> q;
    int x;
    // 初始化
    f[0] = INT_MIN;
    while (q--) {
        std::cin >> op;
        if (op == "I") {
            std::cin >> x;
            left.push_back(x);
            int sz = left.size();
            s[sz] = s[sz - 1] + x;
            f[sz] = std::max(f[sz - 1], s[sz]);
        }
        else if (op == "L") {
            if (left.size()) {
                right.push_back(left.back());
                left.pop_back();
            }
        }
        else if (op == "R") {
            if (right.size()) {
                int num = right.back();
                left.push_back(num);
                int sz = left.size();
                s[sz] = s[sz - 1] + num;
                f[sz] = std::max(f[sz - 1], s[sz]);
                right.pop_back();
            }
        }
        else if (op == "Q") {
            std::cin >> x;
            std::cout << f[x] << std::endl;
        }
        else {
            if (left.size()) {
                left.pop_back();
            }
        }
    }
    return 0;
}
