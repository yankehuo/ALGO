#include <iostream>
#include <algorithm>

const int N = 1e5 + 10;
using LL = long long;
using PLL = std::pair<LL, LL>;
PLL a[N], res[N];
int p[N], l[N], r[N];
int n;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i;
    }
    std::sort(a + 1, a + n + 1);
    a[0].first = -2e9, a[n + 1].first = 2e9;
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1, r[i] = i + 1;
        p[a[i].second] = i;
    }
    for (int i = n; i > 1; --i) {
        int j = p[i], left = l[j], right = r[j];
        LL lv = a[j].first - a[left].first, rv = a[right].first - a[j].first;
        if (lv <= rv) {
            res[i] = {lv, a[left].second};
        }
        else {
            res[i] = {rv, a[right].second};
        }
        l[right] = left, r[left] = right;
    }
    for (int i = 2; i <= n; ++i) {
        std::cout << res[i].first << " " << res[i].second << std::endl;
    }

    return 0;
}