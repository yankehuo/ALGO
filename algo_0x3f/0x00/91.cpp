#include <iostream>
#include <cstring>

// f[i][j]:i(set)-->j 0->j:0->k+k->j
const int N = 21;
int f[1 << N][N];
int n;
int dist[N][N];

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> dist[i][j];
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[1][0] = 0;
    for (int i = 0; i < 1 << n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                for (int k = 0; k < n; ++k) {
                    if ((i ^ (1 << j) >> k & 1)) {
                        f[i][j] = std::min(f[i][j], f[i ^ (1 << j)][k] + dist[k][j]);
                    }
                }
            }
        }
    }
    std::cout << f[(1 << n) - 1][n - 1] << std::endl;
    return 0;
}
