#include <iostream>
#include <cstring>

static const int N = 13;
static int d[N], f[N];

int main() {
    // d[n] = d[n - 1] * 2 + 1
    // f[n] = min f[n - k] * 2 + d[k]
    memset(d, 0x3f, sizeof(d));
    memset(f, 0x3f, sizeof(f));
    f[1] = d[1] = 1;
    for (int i = 2; i < N; ++i) { 
        d[i] = std::min(d[i], 2 * d[i - 1] + 1);
    }
    for (int i = 2; i < 13; ++i) {
        for (int j = 1; j < i; ++j) {
            f[i] = std::min(f[i - j] * 2 + d[j], f[i]);
        }
    }
    for (int i = 1; i < 13; ++i) {
        std::cout << f[i] << std::endl;
    }
    return 0;
}