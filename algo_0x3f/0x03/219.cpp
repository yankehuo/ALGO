#include <iostream>
#include <cstring>

const int N = 210;
int sg[N][N];
int n, m;

int SG(int x, int y) {
    int f[N];
    memset(f, 0, sizeof(f));
    if (sg[x][y] != -1) return sg[x][y];
    for (int i = 2; i <= x - i; ++i) {
        f[SG(i, y) ^ SG(x - i, y)] = 1;
    }
    for (int i = 2; i <= y - i; ++i) {
        f[SG(x, i) ^ SG(x, y - i)] = 1;
    }
    int t = 0;
    while (f[t]) ++t;
    return sg[x][y] = t;
}

int main() {
    memset(sg, -1, sizeof(sg));
    sg[2][2] = sg[2][3] = sg[3][2] = 0;
    while (std::cin >> n >> m) {
        SG(n, m) ? puts("WIN") : puts("LOSE");
    }

    return 0;
}