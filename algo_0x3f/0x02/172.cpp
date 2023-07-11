#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

const int N = 510;
char g[N][N];
int dist[N][N][3];
int n, m;

// lie: 0 stand; 1 row; 2 col;
struct State {
    int x, y, lie;
};

// |------>j
// |
// v
// i
static int d[3][4][3] = {
    // 0,1,2 -> up down left right
    {{-2, 0, 2}, {1, 0, 2}, {0, -2, 1}, {0, 1, 1}},
    {{-1, 0, 1}, {1, 0, 1}, {0, -1, 0}, {0, 2, 0}},
    {{-1, 0, 0}, {2, 0, 0}, {0, -1, 2}, {0, 1, 2}},
};

bool check(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    return g[x][y] != '#';
}

int bfs(State start, State end) {
    std::queue<State> q;
    memset(dist, -1, sizeof(dist));
    dist[start.x][start.y][start.lie] = 0;
    q.push(start);
    while (q.size()) {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            State next = {t.x + d[t.lie][i][0], t.y + d[t.lie][i][1], d[t.lie][i][2]};
            int x = next.x, y = next.y;
            if (!check(x, y)) continue;

            if (next.lie == 0 && g[x][y] == 'E') continue;
            else if (next.lie == 1 && !check(x, y + 1)) continue;
            else if (next.lie == 2 && !check(x + 1, y)) continue;

            if (dist[next.x][next.y][next.lie] == -1) {
                dist[next.x][next.y][next.lie] = dist[t.x][t.y][t.lie] + 1;
                q.push(next);
            }
        }
    }
    return dist[end.x][end.y][end.lie];
}

int main() {
    while (std::cin >> n >> m, n || m) {
        for (int i = 0; i < n; ++i) std::cin >> g[i];
        State start = {-1}, end;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == 'X' && start.x == -1) {
                    if (g[i][j + 1] == 'X') start = {i, j, 1};
                    else if (g[i + 1][j] == 'X') start = {i, j, 2};
                    else start = {i, j, 0};
                } 
                else if (g[i][j] == 'O') end = {i, j, 0};
            }
        }
        int res = bfs(start, end);
        if (res == -1) puts("Impossible");
        else printf("%d\n", res);
    }

    return 0;
}