#include <iostream>
#include <unordered_map>

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator() (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

int n, p, h, m;
const int N = 5010;
using PII = std::pair<int, int>;
std::unordered_map<PII, int, pair_hash> used;

int b[N];

int main() {
    std::cin >> n >> p >> h >> m;
    int l = 0, r = 0;
    while (m--) {
        std::cin >> l >> r;
        if (l > r) {
            std::swap(l, r);
        }
        if (used.count(std::make_pair(l, r))) continue;
        b[l + 1]--, b[r]++;
        used[std::make_pair(l, r)] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        b[i] += b[i - 1];
        std::cout << h + b[i] << std::endl;
    }
    return 0;
}