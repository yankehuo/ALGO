#include <iostream>
#include <algorithm>

const int N = 1010;
struct Node {
    int wt;
    int sz;
    int fa;
    double avg;
} nodes[N];
int n, root;

// 平均值最大的节点先染色
int find() {
    int idx = -1;
    double avg = 0;
    for (int i = 1; i <= n; ++i) {
        if (i != root && nodes[i].avg > avg) {
            avg = nodes[i].avg;
            idx = i;
        }
    }
    return idx;
}

// 自底向上合并
int main() {
    std::cin >> n >> root;
    int x;
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        res += x;
        nodes[i].sz = 1;
        nodes[i].wt = x;
        nodes[i].avg = x;
    }
    int a, b;
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> a >> b;
        nodes[b].fa = a;
    }
    for (int i = 0; i < n - 1; ++i) {
        int cur = find();
        int fa = nodes[cur].fa;
        // 子节点合并到父节点变化量
        res += nodes[fa].sz * nodes[cur].wt;
        nodes[cur].avg = -1;
        // merge
        for (int j = 1; j <= n; ++j) {
            if (nodes[j].fa == cur) {
                nodes[j].fa = fa;
            }
        }
        nodes[fa].wt += nodes[cur].wt;
        nodes[fa].sz += nodes[cur].sz;
        nodes[fa].avg = (double)nodes[fa].wt / nodes[fa].sz;
    }
    std::cout << res << std::endl;
    return 0;
}
