#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 1e5 + 10, M = 1e4 + 10;
const int INF = 1e9;
struct Node {
    int op, x, y, z;
} q[2 * N], lq[2 * N], rq[2 * N];
int n, m, t, c[N], ans[N];

int lowbit(int x) {
    return x & -x;
}

void change(int x, int y) {
    for (; x <= n; x += lowbit(x)) {
        c[x] += y;
    }
}

int ask(int x) {
    int res = 0;
    for (; x;  x -= lowbit(x)) {
        res += c[x];
    }
    return res;
}

void solve(int lval, int rval, int st, int ed) { // lval,rval,lt,rt
    if (st > ed) return;
    if (lval == rval) {
        for (int i = st; i <= ed; ++i) {
            if (q[i].op > 0) {
                ans[q[i].op] = lval;
            }
        }
        return;
    }
    int mid = lval + rval >> 1;
    int lt = 0, rt = 0;
    for (int i = st; i <= ed; ++i) {
        if (q[i].op == 0) {
            if (q[i].y <= mid) change(q[i].x, 1), lq[++lt] = q[i];
            else rq[++rt] = q[i];
        }
        else {
            int cnt = ask(q[i].y) - ask(q[i].x - 1);
            if (cnt >= q[i].z) lq[++lt] = q[i];
            else q[i].z -= cnt, rq[++rt] = q[i];
        }
    }
    // why from ed to st
    for (int i = ed; i >= st; --i) {
        if (q[i].op == 0 && q[i].y <= mid) {
            change(q[i].x, -1);
        }
    }
    for (int i = 1; i <= lt; ++i) {
        q[st + i - 1] = lq[i];
    }
    for (int i = 1; i <= rt; ++i) {
        q[st + lt + i - 1] = rq[i];
    }
    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);

}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        q[++t].op = 0;
        q[t].x = i;
        std::cin >> q[t].y;
    }
    for (int i = 1; i <= m; ++i) {
        q[++t].op = i;
        std::cin >> q[t].x >> q[t].y >> q[t].z; // l,r,k
    }
    solve(-INF, INF, 1, t);
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", ans[i]);
    }

    return 0;
}