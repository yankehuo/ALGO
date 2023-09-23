#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>

// if has zero rows, then k->k-1
// rank r
// ai ^ ai is not allowed, so topic space and xor space are different
// k-->binary code
using LL = long long;
const int N = 1e4 + 10;
int T;
int n;
LL a[N];
int q;
bool has_zero = false;
LL k;
int rank;

void gauss() {
    int r, c;
    has_zero = false;
    int col = 63;
    for (r = 0, c = 0; c < n; ++c) {
        int t = r;
        for (int i = r + 1; i < n; ++i) {
            if (a[i] >> c & 1) {
                t = i;
            }
        }
        if (!(a[t] >> c & 1)) {
            continue;
        }
        std::swap(a[t], a[r]);
        for (int i = r + 1; i < n; ++i) {
            for (int j = col; j >= c; --j) {
                LL tmp = (a[i] >> j & 1) ^ ((a[r] >> j & 1) & (a[i] >> c & 1));
                a[i] |= tmp == 1LL ? (1 << j) : 0LL;
            }
        }
        ++r;
        rank = r;
    }
    if (r < n) {
        has_zero = true;
    }
}
void print_out() {
    puts("=============================");
    for (int i = 0; i < n; ++i) {
        char s[66];
        itoa(a[i], s, 2);
        printf("%8s\n", s);
    }
    puts("=============================");
}

int main() {
    std::cin >> T;
    int idx = 0;
    while (T--) {
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        gauss();
        print_out();
        printf("Case #%d:\n", ++idx);
        std::cin >> q;
        while (q--) {
            std::cin >> k;
            if (has_zero) --k;
            LL res = 0;
            if (k >= 1LL << rank) puts("-1");
            else {
                for (int i = rank - 1; i >= 0; --i) {
                    if (k >> i & 1) {
                        res ^= a[rank - i - 1];
                    }
                }
                printf("%lld\n", res);
            }
        }
    }
    return 0;
}
