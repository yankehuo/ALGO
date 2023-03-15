#include <iostream>
#include <algorithm>
#include <cmath>

const int N = 1010;
using PDD = std::pair<double, double>;
double eps = 1e-6;
PDD range[N];
int n, d;

int main() {
    std::cin >> n >> d;
    int x, y;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        if (y > d) {
            std::cout << "-1" << std::endl;
            return 0;
        }
        double len = sqrt(d * d - y * y);
        range[i] = {x - len, x + len};
    }
    std::sort(range, range + n);
    double ed = -1e9;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        auto cur = range[i];
        if (cur.first > ed + eps) {
            ++res;
            ed = cur.second;
        }
        else {
            ed = std::min(ed, cur.second);
        }
    }
    std::cout << res << std::endl;

    return 0;
}