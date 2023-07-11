#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 16, M = N * N + 1;
int map[1 << N], ones[1 << N];
char str[N][N + 1];
int state[N][N];
int bstate[M][N][N];
int bstate2[M][N][N];
char bstr[M][N][N + 1];

int lowbit(int x) {
    return x & -x;
}

void draw(int x, int y, int c) {
    str[x][y] = c + 'A';
    for (int i = 0; i < N; ++i) {
        state[i][y] &= ~(1 << c);
        state[x][i] &= ~(1 << c);
    }
    int tx = x / 4 * 4, ty = y / 4 * 4;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[tx + i][ty + j] &= ~(1 << c);
        }
    }
    state[x][y] = 1 << c;
}

bool dfs(int cnt) {
    if (!cnt) return true;
    int bcnt = cnt;
    memcpy(bstate[bcnt], state, sizeof(state));
    memcpy(bstr[bcnt], str, sizeof(str));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (str[i][j] == '-') {
                if (!state[i][j]) {
                    memcpy(state, bstate[bcnt], sizeof(state));
                    memcpy(str, bstr[bcnt], sizeof(str));
                    return false;
                }
                if (ones[state[i][j]] == 1) {
                    draw(i, j, map[state[i][j]]);
                    --cnt;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        int sor = 0, sand = (1 << N) - 1;
        int drawn = 0;
        for (int j = 0; j < N; ++j) {
            int s = state[i][j];
            sand &= ~(sor & s);
            sor |= s;
            if (str[i][j] != '-') drawn |= state[i][j];
        }
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[bcnt], sizeof(state));
            memcpy(str, bstr[bcnt], sizeof(str));
            return false;
        }
        for (int j = sand; j; j -= lowbit(j)) {
            int t = lowbit(j);
            if (!(drawn & t)) {
                for (int k = 0; k < N; ++k) {
                    if (state[i][k] & t) {
                        draw(i, k, map[t]);
                        --cnt;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        int sor = 0, sand = (1 << N) - 1;
        int drawn = 0;
        for (int j = 0; j < N; ++j) {
            int s = state[j][i];
            sand &= ~(sor & s);
            sor |= s;
            if (str[j][i] != '-') drawn |= state[j][i];
        }
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[bcnt], sizeof(state));
            memcpy(str, bstr[bcnt], sizeof(str));
            return false;
        }
        for (int j = sand; j; j -= lowbit(j)) {
            int t = lowbit(j);
            if (!(drawn & t)) {
                for (int k = 0; k < N; ++k) {
                    if (state[k][i] & t) {
                        draw(k, i, map[t]);
                        --cnt;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        int sor = 0, sand = (1 << N) - 1;
        int drawn = 0;
        for (int j = 0; j < N; ++j) {
            int tx = i / 4 * 4, ty = i % 4 * 4;
            int dx = j / 4, dy = j % 4;
            int s = state[tx + dx][ty + dy];
            sand &= ~(sor & s);
            sor |= s;
            if (str[tx + dx][ty + dy] != '-') drawn |= state[tx + dx][ty + dy];
        }
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[bcnt], sizeof(state));
            memcpy(str, bstr[bcnt], sizeof(str));
            return false;
        }
        for (int j = sand; j; j -= lowbit(j)) {
            int t = lowbit(j);
            if (!(drawn & t)) {
                for (int k = 0; k < N; ++k) {
                    int tx = i / 4 * 4, ty = i % 4 * 4;
                    int dx = k / 4, dy = k % 4;
                    if (state[tx + dx][ty + dy] & t) {
                        draw(tx + dx, ty + dy, map[t]);
                        --cnt;
                        break;
                    }
                }
            }
        }
    }

    if (!cnt) return true;

    int x, y, s = 100;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (str[i][j] == '-' && ones[state[i][j]] < s) {
                s = ones[state[i][j]];
                x = i, y = j;
            }
        }
    }
    memcpy(bstate2[bcnt], state, sizeof(state));
    for (int i = state[x][y]; i; i -= lowbit(i)) {
        memcpy(state, bstate2[bcnt], sizeof(state));
        draw(x, y, map[lowbit(i)]);
        if (dfs(cnt - 1)) return true;
    }
    memcpy(state, bstate[bcnt], sizeof(state));
    memcpy(str, bstr[bcnt], sizeof(str));
    return false;
}

int main() {
    for (int i = 0; i < N; ++i) map[1 << i] = i;
    for (int i = 0; i < (1 << N); ++i) {
        for (int j = i; j; j -= lowbit(j)) {
            ++ones[i];
        }
    }
    while (std::cin >> str[0]) {
        for (int i = 1; i < N; ++i) std::cin >> str[i];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                state[i][j] = (1 << N) - 1;
            }
        }
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (str[i][j] != '-') {
                    draw(i, j, str[i][j] - 'A');
                }
                else {
                    ++cnt;
                }
            }
        }
        dfs(cnt);
        for (int i = 0; i < N; ++i) std::cout << str[i] << std::endl;
        std::cout << std::endl;
    }
    return 0;
}