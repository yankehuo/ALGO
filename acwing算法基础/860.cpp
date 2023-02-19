#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int h[N], ne[M], e[M];
int color[N];
int idx;
int n, m;

void init() {
    idx = 0;
    memset(h, -1, sizeof h);
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u, int c) {
    color[u] = c;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!color[j]) {
            if (!dfs(j, 3 - c)) {
                return false;
            }
        }
        else if (color[j] == c) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    init();
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    bool flag = true;
    for (int i = 1; i <= n; ++i) {
        if (!color[i]) {
            if (!dfs(i, 1)) {
                flag = false;
                break;
            }
        }
    }
    if (flag) puts("Yes");
    else puts("No");
    return 0;
}
