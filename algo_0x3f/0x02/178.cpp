#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

const int N = 1010, M = 2e4;
using PII = std::pair<int, int>;
using PIII = std::pair<int, std::pair<int, int>>;
int h[N], e[M], ne[M], w[M], idx;
int rh[N];
int dist[N], v[N];
int f[N];
int n, m;
int S, T, K;

void add(int *h, int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void init() {
    memset(h, -1, sizeof(h));
    memset(rh, -1, sizeof(rh));
}

// dis, idx
void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[T] = 0;
    std::priority_queue<PII, std::vector<PII>, std::greater<>> hp;
    memset(v, 0, sizeof(v));
    hp.push({0, T});
    while (hp.size()) {
        auto t = hp.top();
        hp.pop();
        int dis = t.first, cur = t.second;
        if (v[cur]) continue; 
        v[cur] = 1;
        for (int i = rh[cur]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[cur] + w[i]) {
                dist[j] = dist[cur] + w[i];
                hp.push({dist[j], j});
            }
        }
    }
    // memcpy(f, dist, sizeof(dist));
}

int a_star() {
    std::priority_queue<PIII, std::vector<PIII>, std::greater<>> hp;
    memset(v, 0, sizeof(v));
    dist[S] = 0;
    hp.push({dist[S], {0, S}});
    memset(v, 0, sizeof(v));
    while (hp.size()) {
        auto t = hp.top();
        hp.pop();
        int esti = t.first, real = t.second.first, cur = t.second.second;
        if (v[cur] >= K) continue;
        ++v[cur];
        if (cur == T && v[T] == K) return real;
        for (int i = h[cur]; ~i; i = ne[i]) {
            int j = e[i];
            if (v[j] < K) {
                hp.push({real + w[i] + dist[j], {real + w[i], j}});
            }
        }
    }
    return -1;
}

int main() {
    std::cin >> n >> m;
    int a, b, c;
    init();
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        add(h, a, b, c);
        add(rh, b, a, c);
    }
    std::cin >> S >> T >> K;
    if (S == T) K++;
    dijkstra();
    printf("%d\n", a_star());

    return 0;
}