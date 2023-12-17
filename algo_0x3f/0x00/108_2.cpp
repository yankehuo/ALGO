#include <iostream>
#include <cstring>
#include <algorithm>


const int N = 25e4 + 10;
int a[N], b[N];
int ca[N], cb[N];
int n;

int lowbit(int x) {
    return x & -x;
}

int ask(int *arr, int x) {
    int ans = 0;
    for (; x; x -= lowbit(x)) {
        ans ^= arr[x];
    }
    return ans;
}

int add(int *arr, int x, int y) {
    for (; x <= n * n; x += lowbit(x)) {
        arr[x] ^= y;
    }
}

int main() {
    while (std::cin >> n) {
        int ans0 = 0, ans1 = 0;
        memset(ca, 0, sizeof(ca));
        memset(cb, 0, sizeof(cb));
        for (int i = 1; i <= n * n; ++i) std::cin >> a[i];
        for (int i = 1; i <= n * n; ++i) std::cin >> b[i];
        for (int i = n * n; i >= 1; --i) {
            if (a[i]) {
                ans0 ^= ask(ca, a[i] - 1);
                add(ca, a[i], 1);
            }
            if (b[i]) {
                ans1 ^= ask(cb, b[i] - 1);
                add(cb, b[i], 1);
            }
        }
        if (ans0 == ans1) {
            puts("TAK");
        }
        else {
            puts("NIE");
        }
    }

    return 0;
}