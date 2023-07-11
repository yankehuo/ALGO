#include <iostream>
#include <cstring>
#include <queue>

int n, m;
int a, b, c;
int cap, start, end;
int q;
// split up the point
const int N = 1010, M = 2e4 + 10, C = 110;
int p[N];
int e[M], ne[M], w[M], h[N];
int idx;
int dist[N][C], v[N][C];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void init() {
    memset(h, -1, sizeof(h));
    idx = 0;
}

struct Node {
    int price, u, fuel;
    bool operator<(const Node &rhs) const {
        return price > rhs.price;
    }
};

int dijkstra(int cap, int start, int end) {
    memset(dist, 0x3f, sizeof(dist));
    memset(v, 0, sizeof(v));
    std::priority_queue<Node> hp;
    hp.push({0, start, 0});
    dist[start][0] = 0;

    while (hp.size()) {
        auto t = hp.top();
        hp.pop();
        int price = t.price, u = t.u, fuel = t.fuel;
        if (u == end) return price;
        if (v[u][fuel]) continue;

        if (fuel + 1 <= cap) {
            if (dist[u][fuel + 1] > price + p[u]) {
                dist[u][fuel + 1] = price + p[u];
                hp.push({dist[u][fuel + 1], u, fuel + 1});
            }
        }
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if (fuel >= w[i]) {
                if (dist[j][fuel - w[i]] > price) {
                    dist[j][fuel - w[i]] = price;
                    hp.push({dist[j][fuel - w[i]], j, fuel - w[i]});
                }
            }
        }
    }
    return -1;
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) std::cin >> p[i];
    init();
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    std::cin >> q;
    while (q--) {
        std::cin >> cap >> start >> end;
        int res = dijkstra(cap, start, end);
        if (res == -1) puts("impossible");
        else printf("%d\n", res);
    }

    return 0;
}
