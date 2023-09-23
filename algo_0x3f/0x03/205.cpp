// f[n] = [fn-1 fn] * [0 1]
//                    [1 1]
#include <iostream>
#include <cstring>

const int MOD = 1e4;

void mul(int f[2], int a[2][2]) {
    int c[2];
    memset(c, 0, sizeof(c));
    for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
            c[j] = (c[j] + (long long)f[k] * a[k][j]) % MOD;
        }
    }
    memcpy(f, c, sizeof(c));
}

void mulself(int a[2][2]) {
    int c[2][2];
    memset(c, 0, sizeof(c));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                c[i][j] = (c[i][j] + (long long)a[i][k] * a[k][j]) % MOD;
            }
        }
    }
    memcpy(a, c, sizeof(c));
}

int main() {
    int n;
    while (std::cin >> n, n != -1) {
        int f[2] = {0, 1};
        int a[2][2] = {0, 1, 1, 1};
        for (; n; n >>= 1) {
            if (n & 1) mul(f, a);
            mulself(a);
        }
        printf("%d\n", f[0]);
    }
    return 0;
}