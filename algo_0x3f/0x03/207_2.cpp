#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

const double EPS = 1e-8;
const int N = 20;
double a[N][N], b[N];
double tmp[N][N];
int n;

void gauss() {
    int r, c;
    for (r = 0, c = 0; c < n; ++c) {
        for (int i = r + 1; i < n; ++i) {
            if (fabs(a[i][c]) > EPS) {
                for (int j = c; j < n; ++j) {
                    std::swap(a[r][j], a[i][j]);
                }
                std::swap(b[i], b[r]);
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i == r) continue;
            double rate = a[i][c] / a[r][c];
            for (int j = c; j < n; ++j) {
                a[i][j] -= a[r][j] * rate;
            }
            b[i] -= b[r] * rate;
        }
        ++r;
    }

    for (int i = 0; i < n; ++i) {
        b[i] /= a[i][i];
    }
}

void print_out() {
    puts("=====================");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
    puts("=====================");
    for (int i = 0; i < n; ++i) {
        printf("%.3f ", b[i]);
    }
    puts("");
}

int main() {
    std::cin >> n;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> tmp[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 2 * (tmp[i][j] - tmp[i + 1][j]);
            b[i] += tmp[i][j] * tmp[i][j] - tmp[i + 1][j] * tmp[i + 1][j];
        }
    }
    gauss();
    print_out();

    return 0;
}