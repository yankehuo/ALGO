#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

const int N = 1010;
char a[N][N];
int n, m;
int dist[N][N];
using PII = std::pair<int, int>;
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

void bfs() {
    std::queue<PII> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '1') {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (q.size()) {
        auto t = q.front();
        q.pop();
        int x = t.first, y = t.second;
        for (int i = 0; i < 4; ++i) {
            int tx = dx[i] + x, ty = dy[i] + y;
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (dist[tx][ty] == -1) {
                dist[tx][ty] = dist[x][y] + 1;
                q.push({tx, ty});
            }
        }
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    memset(dist, -1, sizeof(dist));
    bfs();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << dist[i][j] << " ";
        }
        puts("");
    }
    return 0;
}