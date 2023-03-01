#include <iostream>

int n, m;
const int N = 1e5 + 10;
std::pair<std::string, int> si[N];

int calc(int bit, int cur) {
    for (int i = 0; i < n; ++i) {
        std::string op = si[i].first;
        int num = si[i].second >> bit & 1;
        if (op == "AND") {
            cur &= num;
        }
        else if (op == "OR") {
            cur |= num;
        }
        else {
            cur ^= num;
        }
    }
    return cur;
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> si[i].first >> si[i].second;
    }
    int val = 0, res = 0;
    for (int i = 29; i >= 0; --i) {
        int res1 = calc(i, 1);
        int res0 = calc(i, 0);
        if (val + (1 << i) <= m && res0 < res1) {
            val += 1 << i;
            res += 1 << i;
        }
        else {
            res += res0 << i;
        }
    }
    std::cout << res << std::endl;

    return 0;
}