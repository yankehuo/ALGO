#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 3e4 + 10;
int T;
int fa[N], d[N], sz[N];

void init() {
    for (int i = 1; i < N; ++i) {
        fa[i] = i;
        d[i] = 0; // down to top
        sz[i] = 1; // top to down
    }
}

int get(int x) {
    if (fa[x] != x) {
        int u = get(fa[x]);
        d[x] += d[fa[x]];
        fa[x] = u;
    }
    return fa[x];
}

void merge(int x, int y) {
    int u = get(x), v = get(y);
    fa[u] = v;
    d[u] = sz[v];
    sz[v] += sz[u];
}

int main() {
    init();
    std::cin >> T;
    char op;
    int x, y;
    while (T--) {
        std::cin >> op >> x >> y;
        if (op == 'M') {
            // M 2 3
            // M 2 4
            // M 2 4
            // 如果相同还merge，会重复累加size，导致d变化
            if (get(x) != get(y))
                merge(x, y);
        }
        else {
            if (get(x) == get(y)) {
                printf("%d\n", std::max(0, abs(d[x] - d[y]) - 1));
            }
            else {
                puts("-1");
            }
        }
    }
    // for (int i = 1; i <= 4; ++i) 
    //     std::cout << fa[i] << ", ";
    //     std::cout << std::endl;
    return 0;
}