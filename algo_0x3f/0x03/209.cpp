#include <iostream>
#include <cstring>
#include <cmath>

const int N = 510;
const double EPS = 1e-6;
long double a[N][N];
int cost[N];
int n, m;
int num;
int res;

void read_in() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // std::cin >> a[i][j];
            scanf("%llf", &a[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> cost[i];
    }
}

int gauss() {
    int r, c;
    for (c = 0, r = 0; c < m; ++c) {
        // 判断该列当中所有小于eps的数值，continue
        int t = n;
        for (int i = r; i < n; ++i) {
            if (fabs(a[i][c]) < EPS) continue;
            if (n == t || cost[t] > cost[i]) {
                t = i;
            }
        }
        // if (fabs(a[t][c]) < EPS) continue;
        if (t == n) continue;
        for (int j = c; j < m; ++j) {
            std::swap(a[t][j], a[r][j]);
        }
        std::swap(cost[t], cost[r]);
        for (int j = m; j >= c; --j) {
            a[r][j] /= a[r][c];
        }
        for (int i = r + 1; i < n; ++i) {
            if (fabs(a[i][c]) > EPS) {
                for (int j = m; j >= c; --j) {
                    a[i][j] -= a[r][j] * a[i][c];
                }
            }
        }
        res += cost[r];
        ++r;
    }
    num = r;
    return 0;
}

void print_out() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
    printf("%d %d\n", num, res);
}

int main() {
    read_in();
    int t = gauss();
    print_out();
    return 0;
} 