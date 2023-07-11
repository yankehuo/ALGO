#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>

const int N = 3e4 + 10, M = 2 * N;
int h[N], e[M], ne[M], deg[N];
int idx, tot;
int n, m;
int arr[N];
std::bitset<N> f[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    ++deg[b];
}

void toposort() {
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    while (q.size()) {
        int u = q.front(); 
        q.pop();
        arr[tot++] = u;
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
}

void calc() {
    for (int i = tot - 1; i >= 0; --i) {
        int u = arr[i];
        f[u][u] = 1;
        for (int j = h[u]; ~j; j = ne[j]) {
            int v = e[j];
            f[u] |= f[v];
        }
    }
}

int main() {
    std::cin >> n >> m;
    int a, b;
    std::memset(h, -1, sizeof(h));
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        add(a, b);
    }
    toposort();
    calc();
    for (int i = 1; i <= n; ++i) {
        std::cout << f[i].count() << std::endl;
    }
    return 0;
}