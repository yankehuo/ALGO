#include <iostream>
#include <cstring>

const int N = 9;
int map[1 << N];
int ones[1 << N];
int row[N], col[N], cell[N / 3][N / 3];
char s[N * N + 1];

int lowbit(int x) {
    return x & -x;
}

// 哪些位可以填
int get(int x, int y) {
    return row[x] & col[y] & cell[x / 3][y / 3];
}

bool dfs(int cnt) {
    if (!cnt) return true;
    int minv = 10;
    int x, y;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s[i * 9 + j] == '.') {
                int t = ones[get(i, j)];
                if (t < minv) {
                    minv = t;
                    x = i, y = j;
                }
            }
        }
    }
    // 从最少方案数开始
    for (int i = get(x, y); i; i -= lowbit(i)) {
        int t = map[lowbit(i)];
        row[x] -= 1 << t;
        col[y] -= 1 << t;
        cell[x / 3][y / 3] -= 1 << t;
        s[x * 9 + y] = t + '1';
        if (dfs(cnt - 1)) return true;
        row[x] += 1 << t;
        col[y] += 1 << t;
        cell[x / 3][y / 3] += 1 << t;
        s[x * 9 + y] = '.';
    }
    return false;
}

int main() {
    // 每一位可以填的数字,0可以填1,1可以填2
    for (int i = 0; i < N; ++i) map[1 << i] = i;
    // 有多少个1
    for (int i = 0; i < 1 << N; ++i) {
        int t = 0;
        for (int j = i; j; j -= lowbit(j)) ++t;
        ones[i] = t;
    }
    while (scanf("%s", s), s[0] != 'e') {
        for (int i = 0; i < N; ++i) {
            row[i] = col[i] = (1 << N) - 1;
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cell[i][j] = (1 << N) - 1;
            }
        }
        int cnt = 0; // 可以填的数字个数
        for (int i = 0, k = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j, ++k) {
                if (s[k] != '.') {
                    int t = s[k] - '1';
                    row[i] -= 1 << t;
                    col[j] -= 1 << t;
                    cell[i / 3][j / 3] -= 1 << t;
                }
                else {
                    ++cnt;
                }
            }
        }
        dfs(cnt);
        std::cout << s << std::endl;
    }
    return 0;
}