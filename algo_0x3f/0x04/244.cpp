#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

const int N = 1e5 + 10;
int a[N];
int c[N]; // for prefix, tree arr
int h[N];
int n;

int lowbit(int x) {
    return x & -x;
}

int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) {
        res += c[x];
    }
    return res;
}

void add(int x, int y) {
    for (; x <= n; x += lowbit(x)) {
        c[x] += y;
    }
}

void init() {
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        c[i] = lowbit(i);
    }
}

void calc() {
    for (int i = n; i >= 1; --i) {
        int l = 1, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (ask(mid) < a[i] + 1) l = mid + 1;
            else r = mid;
        }
        h[i] = l;
        add(l, -1);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", h[i]);
    }
}

void calc_2() {
    int t = std::log2(n);
    for (int i = n; i >= 1; --i) {
        int pos = 0, sum = 0;
        for (int j = t; j >= 0; --j) {
            if (pos + (1 << j) <= n && sum + c[pos + (1 << j)] < a[i] + 1) {
                sum += c[pos + (1 << j)];
                pos += (1 << j);
            }
        }
        h[i] = pos + 1;
        add(pos + 1, -1);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", h[i]);
    }
}

int main() {
    init();
    // calc();
    calc_2();

    return 0;
}