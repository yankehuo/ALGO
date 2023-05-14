#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 2e6 + 10;
char str[N];
const int P = 13331;
using ULL = unsigned long long;
ULL hl[N], hr[N], p[N];

ULL get(ULL *h, int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    p[0] = 1;
    int cnt = 0;
    while (std::cin >> str + 1, strcmp(str + 1, "END")) {
        int len = strlen(str + 1) * 2;
        for (int i = len; i > 0; i -= 2) {
            str[i] =  str[i / 2];
            str[i - 1] = 'a' + 26;
        }
        str[++len] = 'z' + 1;

        for (int i = 1, j = len; i <= len; ++i, --j) {
            hl[i] = hl[i - 1] * P + (str[i] - 'a' + 1);
            hr[i] = hr[i - 1] * P + (str[j] - 'a' + 1);
            p[i] = p[i - 1] * P;
        }
        int res = 1;
        for (int i = 1; i <= len; ++i) {
            int r = std::min(i - 1, len - res);
            if (res >= r || get(hl, i - res, i - 1) != get(hr, len - (i + res) + 1, len - (i + 1) + 1)) continue;
            while (res <= r && get(hl, i - res, i - 1) == get(hr, len - (i + res) + 1, len - (i + 1) + 1)) {
                ++res;
                // std::cout << "i:" << i << "res:" << res << " ";
            }
            --res;
            // std::cout << std::endl;
            // std::cout << res << " ";
        }
        printf("Case %d: %d\n", ++cnt, res);
    }
    return 0;
}