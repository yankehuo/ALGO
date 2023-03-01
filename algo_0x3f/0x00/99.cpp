#include <iostream>

// s[i, j] = s[i, j - 1] + s[i - 1, j] - s[i - 1][j - 1] + a[i, j]
int n, r;
const int N = 5010;
int s[N][N]{};

int main() {
    std::cin >> n >> r;
    int x = 0, y = 0, w = 0;
    // idx begin from 1...
    while (n--) {
        std::cin >> x >> y >> w;
        s[++x][++y] += w;
    }
    for (int i = 1; i <= 5001; ++i) {
        for (int j = 1; j <= 5001; ++j) {
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    int res =0;
    // r的范围
    r = std::min(r, 5001);
    for (int i = r; i <= 5001; ++i) {
        for (int j = r; j <= 5001; ++j) {
            res = std::max(res, s[i][j] + s[i - r][j - r] - s[i][j - r] - s[i - r][j]);
        }
    }
    std::cout << res << std::endl;
    return 0;

}