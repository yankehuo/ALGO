#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 1e5 + 10;
int a[N];
int t[N];
int n, m;

int lowbit(int x) {
    return x & -x;
}

int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) {
        res += t[x];
    }
    return res;
}

void add(int x, int y) {
    for (; x <= n; x += lowbit(x)) {
        t[x] += y;
    }
}

int main() {
    std::cin >> n >> m;
    char op;
    int l, r, d;
    int x;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    while (m--) {
        std::cin >> op;
        if (op == 'C') {
            std::cin >> l >> r >> d;
            add(l, d);
            add(r + 1, -d);
        }
        else {
            std::cin >> x;
            printf("%d\n", a[x] + ask(x));
        }
    }
    return 0;
}