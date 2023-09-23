#include <iostream>
#include <cstring>
#include <cmath>

const int N = 20;
const double EPS = 1e-6;
double id[N][N];
double a[N][N];
int n;

void read_in() {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%lf", &id[i][j]);
        }
    }
}

void make_mat() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 2 * (id[i][j] - id[i + 1][j]);
            a[i][n] += id[i][j] * id[i][j] - id[i + 1][j] * id[i + 1][j];
        }
    }
}

int gauss() {
    int r, c;
    for (c = 0, r = 0; c < n; ++c) {
        int t = r;
        for (int i = r; i < n; ++i) {
            if (fabs(a[i][c]) > fabs(a[t][c])) {
                t = i;
            }
        }
        if (fabs(a[t][c]) < EPS) continue;
        for (int j = c; j <= n; ++j) std::swap(a[t][j], a[r][j]);
        for (int j = n; j >= c; --j) a[r][j] /= a[r][c];
        for (int i = r + 1; i < n; ++i) {
            if (fabs(a[i][c]) > EPS) {
                for (int j = n; j >= c; --j) {
                    a[i][j] -= a[r][j] * a[i][c];
                }
            }
        }
        ++r;
    }
    if (r < n)  {
        for (int i = r; i < n; ++i) {
            if (fabs(a[i][n]) > EPS) {
                return 2; // zero
            }
        }
        return 1; // more
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            a[i][n] -= a[j][n] * a[i][j];
        }
        if (fabs(a[i][n]) < EPS) a[i][n] = 0;
    }
    return 0; // one
}

void print_out() { 
    for (int i = 0; i < n; ++i) {
        printf("%.3f ", a[i][n]);
    }
    printf("\n");
}

int main() {
    read_in();
    make_mat();
    int t = gauss();
    if (!t) {
        print_out();
    }
    return 0;
}
