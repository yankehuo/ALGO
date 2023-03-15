#include <iostream>

int n;
const int N = 1e5 + 10;
int a[N];

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    int res = 0;
    for (int i = 1; i < n; ++i) {
        res += std::max(0, a[i] - a[i - 1]);
    }
    std::cout << res << std::endl;

    return 0;
}