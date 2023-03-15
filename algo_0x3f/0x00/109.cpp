#include <iostream>
#include <algorithm>

int K;
const int N = 5e5 + 10;
int n, m;
long long t;
long long a[N], b[N], tmp[N];

bool check(int l, int mid, int r) {
    for (int i = mid + 1; i <= r; ++i) {
        b[i] = a[i];
    }
    std::sort(b + mid + 1, b + r + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (b[i] <= b[j]) {
            tmp[k++] = b[i++];
        }
        else {
            tmp[k++] = b[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = b[i++];
    }
    while (j <= r) {
        tmp[k++] = b[j++];
    }
    long long sum = 0;
    for (int i = 0; i < m && i < k; ++i, --k) {
        sum += (tmp[k - 1] - tmp[i]) * (tmp[k - 1] - tmp[i]);
    }
    return sum <= t;
}

int main() {
    std::cin >> K;
    while (K--) {
        std::cin >> n >> m >> t;
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        int r = 0, l = 0;
        b[0] = a[0]; // for complete data 
        int res = 0;
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
                    p /= 2;
                }
            }
            ++res;
            l = r + 1;
        }
        std::cout << res << std::endl;
    }
    return 0;
}