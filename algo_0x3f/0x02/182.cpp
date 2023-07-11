#include <iostream>
#include <cstring>
#include <vector>
using std::vector;

const int N = 61;
vector<int> square[N];
int v[N];
int T;
int n, k;
int idx = 0, max_depth = 0;

void add(int r, int c, int len) {
    int d = 2 * n + 1;
    auto &t = square[idx];
    t.clear();
    for (int i = 0; i < len; ++i) {
        t.push_back(1 + r * d + c + i);
        t.push_back(1 + (r + len) * d + c + i);
        t.push_back(1 + n + r * d + c + i * d);
        t.push_back(1 + n + r * d + c + i * d + len);
    }
    idx++;
}

bool check(vector<int> &sq) {
    for (int i = 0; i < sq.size(); ++i) {
        if (v[sq[i]]) return false;
    }
    return true;
}

int f() {
    static int bk[N];
    memcpy(bk, v, sizeof(v));
    int res = 0;
    for (int i = 0; i < idx; ++i) {
        if (check(square[i])) {
            for (int j = 0; j < square[i].size(); ++j) {
                v[square[i][j]] = 1;
            }
            ++res;
        }
    }
    memcpy(v, bk, sizeof(v));
    return res;
}

bool dfs(int depth) {
    if (depth + f() > max_depth) return false;
    for (int i = 0; i < idx; ++i) {
        if (check(square[i])) {
            for (int j = 0; j < square[i].size(); ++j) {
                v[square[i][j]] = 1;
                if (dfs(depth + 1)) return true;
                v[square[i][j]] = 0;
            }
            return false;
        }
    }
    return true;
}

int main() {
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        idx = 0;
        memset(v, 0, sizeof(v));
        for (int len = 1; len <= n; ++len) {
            for (int r = 0; r <= n - len; ++r) {
                for (int c = 0; c <= n - len; ++c) {
                    add(r, c, len);
                }
            }
        }
        std::cin >> k;
        int x;
        for (int i = 0; i < k; ++i) {
            std::cin >> x;
            v[x] = 1;
        }
        max_depth = 0;
        while (!dfs(0)) ++max_depth;
        printf("%d\n", max_depth);
    }

    return 0;
}