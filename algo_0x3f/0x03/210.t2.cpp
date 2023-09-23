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
        for (int i = r + 1; i < n; ++i) {
            if (a[i] > a[r]) {
                std::swap(a[i], a[r]);
            }
        }
        if (!a[r]) {
            has_zero = true;
            rank = r;
            break;
        }
        for (int i = col; i >= 0; --i) {
            if (a[r] >> i & 1) {
                for (int j = 0; j < n; ++j) {
                    if (j != r && (a[j] >> i & 1)) {
                        a[j] ^= a[r];
                    }
                }
                break;
            }
        }
        ++r;
        rank = r;
    }
}

void print_out() {
    puts("=============================");
    printf("rank: %d\n", rank);
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
