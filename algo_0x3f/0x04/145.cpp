#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 1e4 + 10;
using PII = std::pair<int, int>;
PII pa[N];
int p[N];
int n;
int d = 0;

int get(int x) {
    if (x == p[x]) return x;
    return p[x] = get(p[x]);
}

int calc() {
    int res = 0;
    for (int i = 0; i <= d; ++i) {
        p[i] = i;
    }
    for (int i = n; i > 0; --i) {
        int r = get(pa[i].second);
        if (r) {
            res += pa[i].first;
            p[r] = r - 1;
        }
    }
    return res;
}

int main() {
    while (std::cin >> n) {
        for (int i = 1; i <= n; ++i) {
            std::cin >> pa[i].first >> pa[i].second; // p d
            d = std::max(d, pa[i].second);
        }
        std::sort(pa + 1, pa + n + 1);
        printf("%d\n", calc());
    }
    return 0;
}