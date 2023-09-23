#include <iostream>
#include <cstring>
#include <queue>

int n, m;
const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], w[M], idx;
double dis[N];
int deg[N], out[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void init() {
    idx = 0;
    memset(h, -1, sizeof(h));
}

void calc() {
    std::queue<int> q;
    q.push(n);
    while (q.size()) {
        auto t = q.front();
        q.pop();
        int u = t;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            int wt = w[i];
            dis[v] += (dis[u] + wt) / deg[v];
            --out[v];
            if (out[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    init();
    std::cin >> n >> m;
    int a, b, c;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        add(b, a, c);
        ++deg[a], ++out[a];
    }
    calc();
    printf("%.2lf\n", dis[1]);

return 0;
}