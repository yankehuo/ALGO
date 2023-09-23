#include <iostream>
#include <cstring>

// state matrix, transfer matrix
const int N = 72, M = 22;
using LL = long long;
int n, m, t, act;
LL f[N], a[N][N][N];
LL res;
LL prod[N][N]; // 前60s a乘积
int id[M][M]; // 对应act编号
char s[M]; // 临时记录编号
char ops[M][M]; // act序列
int pos[N][N]; // (i,j)对应的操作序列字符位置
int p;

int num(int x, int y) {
    return (x - 1) * m + y;
}

// mul vs muself: the number of parameters
void mul(LL f[N], LL a[N][N]) {
    LL c[N];
    memset(c, 0, sizeof(c));
    for (int j = 0; j <= p; ++j) {
        for (int k = 0; k <= p; ++k) {
            c[j] += f[k] * a[k][j];
        }
    }
    memcpy(f, c, sizeof(c));
}

void mulself(LL a1[N][N], LL a2[N][N]) {
    LL c[N][N];
    memset(c, 0, sizeof(c));
    for (int i = 0; i <= p; ++i) {
        for (int j = 0; j <= p; ++j) {
            for (int k = 0; k <= p; ++k) {
                c[i][j] += a1[i][k] * a2[k][j];
            }
        }
    }
    memcpy(a1, c, sizeof(c));
}

void read_in() {
    std::cin >> n >> m >> t >> act;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j) {
            id[i][j] = s[j] - '0' + 1;
        }
    }
    for (int i = 1; i <= act; ++i) {
        scanf("%s", ops[i]);
    }
}

void make_mat() {
    p = n * m;
    for (int k = 1; k <= 60; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                // locate ops by id, pos
                int x = id[i][j], y = pos[i][j];
                char ch = ops[x][y];
                if (ch >= '0' && ch <= '9') {
                    a[k][0][num(i, j)] = ch - '0';
                    a[k][num(i, j)][num(i, j)] = 1;
                }
                else if (ch == 'N' && i > 1) {
                    a[k][num(i, j)][num(i - 1, j)] = 1;
                }
                else if (ch == 'S' && i < n) {
                    a[k][num(i, j)][num(i + 1, j)] = 1;
                }
                else if (ch == 'W' && j > 1) {
                    a[k][num(i, j)][num(i, j - 1)] = 1;
                }
                else if (ch == 'E' && j < m) {
                    a[k][num(i, j)][num(i, j + 1)] = 1;
                }
                pos[i][j] = (y + 1) % strlen(ops[x]);
            }
        }
        a[k][0][0] = 1;
    }
    memcpy(prod, a[1], sizeof(prod));
    for (int k = 2; k <= 60; ++k) {
        mulself(prod, a[k]);
    }

}

void solve() {
    f[0] = 1;
    int q = t / 60, r = t % 60;
    for (; q; q >>= 1) {
        if (q & 1) mul(f, prod);
        mulself(prod, prod);
    }
    for (int i = 1; i <= r; ++i) {
        mul(f, a[i]);
    }
    for (int i = 1; i <= p; ++i) {
        res = std::max(res, f[i]);
    }
}

int main() {
    read_in();
    make_mat();
    solve();
    printf("%lld\n", res);

    return 0;
}