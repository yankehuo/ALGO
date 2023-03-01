#include <iostream>
#include <cstring>

static const int N = 6;
static int n;
static int dx[]{-1, 0, 0, 0, 1}, dy[]{0, 1, 0, -1, 0};
static char arr[N][N]{};
static char backup[N][N]{};

void turn(int x, int y) {
    for (int i = 0; i < 5; ++i) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 0 && tx < 5 && ty >= 0 && ty < 5) {
            arr[tx][ty] ^= 1;
        }
    }
}

int calc() {
    int res = 7;
    for (int i = 0; i < (1 << 5); ++i) {
        memcpy(backup, arr, sizeof(arr));
        int step = 0;
        for (int j = 0; j < 5; ++j) {
            // 变回原样
            if (i >> j & 1) {
                turn(0, j);
                ++step;
            }
        }
        for (int k = 0; k < 4; ++k) {
            for (int j = 0; j < 5; ++j) {
                if (arr[k][j] == '0') {
                    turn(k + 1, j);
                    ++step;
                }
            }
        }
        bool flag = true;
        for (int k = 0; k < 5; ++k) {
            if (arr[4][k] == '0') {
                flag = false;
                break;
            }
        }
        if (flag) {
            res = std::min(res, step);
        }
        memcpy(arr, backup, sizeof(backup));
    }
    return res > 6 ? -1 : res;
}

int main() {
    std::cin >> n;
    while (n--) {
        for (int i = 0; i < 5; ++i) {
            std::cin >> arr[i];
        }
        std::cout << calc() << std::endl;
    }
    return 0;
}