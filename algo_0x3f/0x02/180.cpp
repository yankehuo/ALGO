#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 16;
int seq[N];
int backup[5][N];
int T, n;

int f() {
    int tot = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (seq[i + 1] != seq[i] + 1) ++tot;
    }
    return (tot + 2) / 3;
}

bool check() {
    for (int i = 0; i < n; ++i) {
        if (seq[i] != i + 1) return false;
    }
    return true;
}

bool dfs(int depth, int max_depth) {
    if (depth + f() > max_depth) return false;
    if (check()) return true;
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            for (int k = r + 1; k < n; ++k) { 
                memcpy(backup[depth], seq, sizeof(seq));
                int x, y;
                for (x = r + 1, y = l; x <= k; ++x, ++y) seq[y] = backup[depth][x];
                for (x = l; x <= r; ++x, ++y) seq[y] = backup[depth][x];
                if (dfs(depth + 1, max_depth)) return true;
                memcpy(seq, backup[depth], sizeof(seq));

            }
        }
    }
    return false;
}

int main() {
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 0; i < n; ++i) std::cin >> seq[i];
        int depth = 0;
        while (depth < 5 && !dfs(0, depth)) ++depth;
        if (depth >= 5) puts("5 or more");
        else printf("%d\n", depth);
    }
    return 0;
}