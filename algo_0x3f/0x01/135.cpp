#include <iostream>
#include <climits>

int n, m;
using LL = long long;
const int N = 3e5 + 10;
int q[N], hh, tt;
LL a[N], s[N];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    LL res = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        if (hh <= tt && i - q[hh] > m) ++hh;
        res = std::max(res, s[i] - s[q[hh]]);
        while (hh <= tt && s[q[tt]] >= s[i]) --tt;
        q[++tt] = i;
    }
    std::cout << res << std::endl;

    return 0;
}
