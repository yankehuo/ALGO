#include <iostream>
#include <algorithm>
#include <cstring>

struct Point {
    int x, y, e;
};
const int N = 1e5 + 10, M = 2 * N;
int uniq[M];
Point pa[N];
int idx;
int p[M];
int m;

int get(int x) {
    if (x != p[x]) {
        p[x] = get(p[x]);
    }
    return p[x];
}

int get_idx(int x) {
    return std::lower_bound(uniq + 1, uniq + m + 1, x) - uniq;
}

int main() {
    int T;
    std::cin >> T;
    int n;
    int x, y, e;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            std::cin >> x >> y >> e;
            pa[i] = {x, y, e};
            uniq[2 * i - 1] = x;
            uniq[2 * i] = y;
        }
        std::sort(uniq + 1, uniq + 2 * n + 1);
        // sparse
        m = std::unique(uniq + 1, uniq + 2 * n + 1) - (uniq + 1);
        for (int i = 1; i <= m; ++i) {
            p[i] = i;
        }
        for (int i = 1; i <= n; ++i) {
            if (pa[i].e) {
                p[get(get_idx(pa[i].x))] = get(get_idx(pa[i].y));
            }
        }
        bool flag = 1;
        for (int i = 1; i <= n; ++i) {
            if (pa[i].e == 0 && get(get_idx(pa[i].x)) == get(get_idx(pa[i].y))) {
                flag = 0;
                break;
            }
        }
        if (flag) puts("YES");
        else puts("NO");

    }
    return 0;

}