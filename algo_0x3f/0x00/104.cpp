#include <iostream>
#include <algorithm>

const int N = 1e5 + 10;
int a[N];
int n;

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a, a + n);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += abs(a[i] - a[n / 2]);
    }
    std::cout << res << std::endl;

    return 0;
}