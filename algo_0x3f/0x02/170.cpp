#include <iostream>
#include <cstring>

const int N = 110;
int path[N];
int v[N];
int n;

bool dfs(int u, int depth) {
    if (u == depth) {
        return path[u - 1] == n;
    }
    memset(v, 0, sizeof(v));
    for (int i = u - 1; i >= 0; --i) {
        for (int j = i; j >= 0; --j) {
            int s = path[i] + path[j];
            if (s >= path[u - 1] && s <= n && !v[s]) {
                path[u] = s;
                v[s] = 1;
                if (dfs(u + 1, depth)) return true;
            }
        }
    }
    return false;
}

int main() {
    path[0] = 1;
    while (std::cin >> n, n) {
        int depth = 1;
        while (!dfs(1, depth)) ++depth;
        for (int i = 0; i < depth; ++i) {
            std::cout << path[i] << " "; 
        }
        puts("");
    }
    return 0;
}