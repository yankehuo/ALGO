#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>

using PII = std::pair<int, int>;
const int N = 510;
int T;
int r, c;
char s[N][N];
char ops[] = "\\/\\/";
int mov_pnt[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
int mov_box[4][2] = {{-1, -1}, {-1, 0}, {0, 0}, {0, -1}};
int dist[N][N];
int v[N][N];

int bfs() {
    memset(dist, 0x3f, sizeof(dist));
    memset(v, 0, sizeof(v));
    std::deque<PII> q;
    q.push_back({0, 0});
    dist[0][0] = 0;
    while (q.size()) {
        auto t = q.front();
        q.pop_front();
        int x = t.first, y = t.second;
        if (v[x][y]) continue;
        v[x][y] = 1;
        for (int i = 0; i < 4; ++i) {
            int tx = x + mov_pnt[i][0], ty = y + mov_pnt[i][1];
            int txb = x + mov_box[i][0], tyb = y + mov_box[i][1];
            if (tx >= 0 && tx <= r && ty >= 0 && ty <= c) { // equals
                int w = s[txb][tyb] == ops[i] ? 0 : 1;
                if (dist[tx][ty] > w + dist[x][y]) {
                    dist[tx][ty] = dist[x][y] + w;
                    if (w == 1) {
                        q.push_back({tx, ty});
                    }
                    else {
                        q.push_front({tx, ty});
                    }
                }
            }
        }
    }
    if (dist[r][c] == 0x3f3f3f3f) return -1;
    return dist[r][c];
}

int main() {
    std::cin >> T;
    while (T--) {
        std::cin >> r >> c;
        for (int i = 0; i < r; ++i) std::cin >> s[i];
        int res = bfs();
        if (res == -1) {
            puts("NO SOLUTION");
        }
        else {
            std::cout << res << std::endl;
        }
    }

    return 0;
}