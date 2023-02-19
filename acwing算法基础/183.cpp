#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 9, M = 1 << N;
int g[N][N];
int row[N], col[N], cell[N / 3][N / 3];
int ones[M], map[M];
int res = -1;

int lowbit(int x) {
    return x & -x;
}

void init() {
    for (int i = 0; i < N; ++i) map[1 << i] =i;
    for (int i = 0; i < M; ++i) {
        for (int j = i; j; j -= lowbit(j)) {
            ++ones[i];
        }
    }
    for (int i = 0; i < N; ++i) {
        row[i] = col[i] = cell[i / 3][i % 3] = M - 1;
    }
}

int main() {
    init();
    int cnt = 0, score = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            cin >> x;
            if (x) {
                draw(i, j, x);
                score += get_score(i, j, x);
            }
            else {
                ++cnt;
            }
        }
    }
    dfs(cnt);
    cout << res << endl;

    return 0;
}