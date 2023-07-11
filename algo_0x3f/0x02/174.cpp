#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using PII = std::pair<int, int>;
const int N = 25;
int n, m;
char g[N][N];
struct Node {
    int x, y, dir;
};
std::vector<int> path[N][N][4]; // man from the pre to (j, k, i)
Node pre[N][N][4]; // box: the pre state of now
int v[N][N][4];
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1}; // up down left right
PII dist[N][N][4]; // distance of box and people
int v_man[N][N];
int pre_man[N][N];

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#';
}

int bfs_man(PII start, PII end, PII box, std::vector<int> &seq) {
    memset(v_man, 0, sizeof(v_man));
    memset(pre_man, -1, sizeof(pre_man));
    std::queue<PII> q;
    q.push(start);
    v_man[start.first][start.second] = 1;
    v_man[box.first][box.second] = 1;

    while (q.size()) {
        auto t = q.front();
        q.pop();
        int x = t.first, y = t.second;
        if (t == end) {
            seq.clear();
            while (pre_man[x][y] != -1) {
                int dir = pre_man[x][y] ^ 1;
                seq.push_back(dir);
                x += dx[dir], y += dy[dir];
            }
            return seq.size();
        }

        for (int j = 0; j < 4; ++j) {
            int i = j ^ 1;
            int tx_man = x + dx[i], ty_man = y + dy[i];
            if (check(tx_man, ty_man) && !v_man[tx_man][ty_man]) {
                v_man[tx_man][ty_man] = 1;
                pre_man[tx_man][ty_man] = i;
                q.push({tx_man, ty_man});
            }
        }
    }
    return -1;
}

bool bfs_box(PII man, PII box, Node &end) {
    memset(v, 0, sizeof(v));
    std::queue<Node> q;
    for (int i = 0; i < 4; ++i) {
        int x = box.first, y = box.second;
        int tx_man = x + dx[i], ty_man = y + dy[i];
        int tx_box = x - dx[i], ty_box = y - dy[i];
        std::vector<int> seq;
        if (check(tx_man, ty_man) && check(tx_box, ty_box) && bfs_man(man, {tx_man, ty_man}, box, seq) != -1) {
            v[tx_box][ty_box][i] = 1;
            q.push({tx_box, ty_box, i});
            dist[tx_box][ty_box][i] = {1, seq.size()};
            path[tx_box][ty_box][i] = seq;
            pre[tx_box][ty_box][i] = {x, y, -1};
        }
    }

    bool success = false;
    PII man_d = {1e9, 1e9};
    while (q.size()) {
        auto t = q.front();
        q.pop();
        int x = t.x, y = t.y, dir = t.dir;
        if (g[x][y] == 'T') {
            success = true;
            if (dist[x][y][dir] < man_d) {
                man_d = dist[x][y][dir];
                end = t;
            }
        }

        for (int i = 0; i < 4; ++i) {
            int tx_man = x + dx[i], ty_man = y + dy[i];
            int tx_box = x - dx[i], ty_box = y - dy[i];
            if (check(tx_man, ty_man) && check(tx_box, ty_box)) {
                std::vector<int> seq;
                auto &p = dist[tx_box][ty_box][i];
                int distance = bfs_man({x + dx[dir], y + dy[dir]}, {tx_man, ty_man}, {x, y}, seq);
                if (distance != -1) {
                    PII td = {dist[x][y][dir].first + 1, dist[x][y][dir].second + distance};
                    if (!v[tx_box][ty_box][i]) {
                        v[tx_box][ty_box][i] = 1;
                        q.push({tx_box, ty_box, i});
                        path[tx_box][ty_box][i] = seq;
                        pre[tx_box][ty_box][i] = t;
                        p = td;
                    }
                    else if (p > td) {
                        p = td;
                        path[tx_box][ty_box][i] = seq;
                        pre[tx_box][ty_box][i] = t;
                    }
                }
            }
        }
    }
    return success;
}

int main() {
    int cnt = 1;
    while (std::cin >> n >> m, n || m) {
        for (int i = 0; i < n; ++i) {
           std::cin >> g[i]; 
        }
        printf("Maze #%d\n", cnt++);
        PII man, box;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == 'S') man = {i, j};
                else if (g[i][j] == 'B') box = {i, j};
            }
        }
        Node end;
        if (!bfs_box(man, box, end)) puts("Impossible.");
        else {
            char ops[] = "nswe";
            std::string res;
            while (end.dir != -1) {
                res += ops[end.dir] - 32; // A 65 a 97
                for (auto &dir : path[end.x][end.y][end.dir]) res += ops[dir];
                end = pre[end.x][end.y][end.dir];
            }
            std::reverse(res.begin(), res.end());
            std::cout << res << std::endl;
        }
        puts("");
    }

    return 0;
}