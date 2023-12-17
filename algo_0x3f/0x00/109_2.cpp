#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 5e5 + 10;
int a[N], b[N], tmp[N];
int n, m, t;
int K;

bool check(int l, int mid, int r) {
    for (int i = mid + 1; i <= r; ++i) {
        b[i] = a[i];
    }
    std::sort(b + mid + 1, b + r + 1);
    int i = l, j = mid + 1;
    int k = 0;
    while (i <= mid && j <= r) {
        if (b[i] < b[j]) tmp[k++] = b[i++];
        else tmp[k++] = b[j++];
    }
    while (i <= mid) {
        tmp[k++] = b[i++];
    }
    while (j <= r) {
        tmp[k++] = b[j++];
    }
    int sum = 0;
    for (int i = 0; i < m && i < k; ++i, --k) {
        sum += (tmp[k - 1] - tmp[i]) * (tmp[k - 1] - tmp[i]);
    }
    return sum <= t;
}

int main() {
    std::cin >> K;
    while (K--) {
        std::cin >> n >> m >> t;
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        b[0] = a[0];
        int l = 0, r = 0;
        int ans = 0;
        while (l < n) {
            int p = 1;
            while (p) {
                if (r + p < n && check(l, r, r + p)) {
                    r += p;
                    p *= 2;
                    if (r == n - 1) {
                        break;
                    }
                    for (int i = l, j = 0; i <= r; ++i, ++j) {
                        b[i] = tmp[j];
                    }
                }
                else {
                    p >>= 1;
                }
            }
            ++ans;
            l = r + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}