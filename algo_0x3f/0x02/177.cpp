#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using PII = std::pair<int, int>;
int t;
int n, m;
const int N = 810;
char g[N][N];
int v[N][N]; // 0:no 1:boy 2:girl
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
PII gst[2];

bool check(int x, int y, int step) {
    if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == 'X') return false;
    for (int i = 0; i < 2; ++i) {
        if (abs(x - gst[i].first) + abs(y - gst[i].second) <= step * 2) return false;
    }
    return true;
}

int bfs() {
    std::queue<PII> qb, qg;
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == 'M') qb.push({i, j});
            else if (g[i][j] == 'G') qg.push({i, j});
            else if (g[i][j] == 'Z') gst[idx++] = {i, j};
        }
    }
    int step = 0;
    memset(v, 0, sizeof(v));

    while (qb.size() || qg.size()) {
        ++step;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0, len = qb.size(); j < len; ++j) {
                auto t = qb.front();
                qb.pop();
                int x = t.first, y = t.second;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; ++k) {
                    int tx = x + dx[k], ty = y + dy[k];
                    if (check(tx, ty, step)) {
                        if (v[tx][ty] == 2) return step;
                        else if (v[tx][ty] == 0) {
                            v[tx][ty] = 1;
                            qb.push({tx, ty});
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 1; ++i) {
            for (int j = 0, len = qg.size(); j < len; ++j) {
                auto t = qg.front();
                qg.pop();
                int x = t.first, y = t.second;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; ++k) {
                    int tx = x + dx[k], ty = y + dy[k];
                    if (check(tx, ty, step)) {
                        if (v[tx][ty] == 1) return step;
                        else if (v[tx][ty] == 0) {
                            v[tx][ty] = 2;
                            qg.push({tx, ty});
                        }
                    }
                }
            }
        }

    }
    return -1;
}

int main() {
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        for (int i = 0; i < n; ++i) std::cin >> g[i];
        std::cout << bfs() << std::endl;
    }
    return 0;
}
