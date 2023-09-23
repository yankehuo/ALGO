#include <iostream>
#include <algorithm>

int n;
const int N = 1e5 + 10;
int a[N], b[N];
double ansxor = 0, ansor = 0, ansand = 0;

void calc(int k) {
    int last[2] = {0, 0}, c1 = 0, c2 = 0;
    double w = (double)(1 << k) / n / n;
    for (int i = 1; i <= n; ++i) {
        b[i] = a[i] >> k & 1;
        if (b[i]) {
            ansxor += w;
            ansor += w;
            ansand += w;
        }
        if (!b[i]) {
            ansor += w * last[1] * 2;
        }
        else {
            ansand += w * (i - 1 - last[0]) * 2;
            ansor += w * (i - 1) * 2;
        }
        ansxor += w * (b[i] ? c1 : c2) * 2;
        ++c1;
        if (b[i]) {
            std::swap(c1, c2);
        }
        last[b[i]] = i;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    // 0 to 30, value difference
    for (int i = 30; i >= 0; --i) {
        calc(i);
    }
    printf("%.3lf %.3lf %.3lf\n", ansxor, ansand, ansor);
    return 0;
}