#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 20;
double f[N][N][N][N][5][5]; // for value 0-3 abcd 4 any
const double INF = 1e20;
int A, B, C, D;

double dfs(int a, int b, int c, int d, int x, int y) {
    if (a > 13 || b > 13 || c > 13 || d > 13) return INF;
    double &v = f[a][b][c][d][x][y];
    if (v >= 0) return v;
    int as = a + (x == 0) + (y == 0);
    int bs = b + (x == 1) + (y == 1);
    int cs = c + (x == 2) + (y == 2);
    int ds = d + (x == 3) + (y == 3);
    if (as >= A && bs >= B && cs >= C && ds >= D) {
        return v = 0;
    }
    int sum = as + bs + cs + ds;
    if (54 - sum <= 0) return v = INF;

    v = 1;
    if (a < 13) v += (13.0 - a) / (54 - sum) * dfs(a + 1, b, c, d, x, y);
    if (b < 13) v += (13.0 - b) / (54 - sum) * dfs(a, b + 1, c, d, x, y);
    if (c < 13) v += (13.0 - c) / (54 - sum) * dfs(a, b, c + 1, d, x, y);
    if (d < 13) v += (13.0 - d) / (54 - sum) * dfs(a, b, c, d + 1, x, y);
    if (x == 4) {
        double t = INF;
        for (int i = 0; i < 4; ++i) {
            t = std::min(t, 1.0 / (54 - sum) * dfs(a, b, c, d, i, y));
        }
        v += t;
    }
    if (y == 4) {
        double t = INF;
        for (int i = 0; i < 4; ++i) {
            t = std::min(t, 1.0 / (54 - sum) * dfs(a, b, c, d, x, i));
        }
        v += t;
    }
    return v;
}

int main() {
    std::cin >> A >> B >> C >> D;
    memset(f, -1, sizeof(f));
    double res = dfs(0, 0, 0, 0, 4, 4);
    if (res > INF / 2) res = -1;
    printf("%.3f\n", res);

    return 0;
}