#include <iostream>
#include <cstring>
#include <cmath>

const int N = 32;
int a[N][N];
int res;
int n;

int gauss() {
    int r, c;
    for (c = 1, r = 1; c <= n; ++c) {
        int t = r;
        for (int i = r + 1; i <= n; ++i) {
            if (a[i][c]) {
                t = i;
            }
        }
        if (!a[t][c]) continue;
        for (int j = c; j <= n + 1; ++j) {
            std::swap(a[t][j], a[r][j]);
        }
        /*
        for (int j = n + 1; j >= c; --j) {
            a[r][j] /= a[r][c];
        }
        */
        for (int i = r + 1; i <= n; ++i) {
            for (int j = n + 1; j >= c; --j) {
                // a[i][j] -= a[r][j] * a[i][c]
                a[i][j] ^= a[r][j] & a[i][c];
            }
        }
        ++r;
    }
    res = 1;
    if (r <= n) {
        for (int i = r; i <= n; ++i) {
            if (a[i][n + 1]) {
                return 2;
            }
            res *= 2;
        }
        return 1;
    }
    return 0;
}

int main() {
    int k;
    std::cin >> k;
    int num;
    while (k--) {
        memset(a, 0, sizeof(a));
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i][n + 1];
        }
        for (int i = 1; i <= n; ++i) {
            std::cin >> num;
            a[i][n + 1] ^= num;
            a[i][i] = 1;
        }
        int x, y;
        //       a12x2
        // a21x1
        while (std::cin >> x >> y, x || y) {
            a[y][x] = 1;
        }
        int t = gauss();
        if (t == 2) puts("Oh,it's impossible~!!");
        else printf("%d\n", res);
    }
    return 0;
}