#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 88;
int a[N], v[N];
int len, cnt;
int n;

bool dfs(int u, int cab, int start) {
    if (u >= cnt) return true;
    if (cab == len) return dfs(u + 1, 0, 0);
    int fail = 0;
    for (int i = start; i < n; ++i) {
        if (!v[i] && a[i] + cab <= len && fail != a[i]) {
            v[i] = 1;
            if (dfs(u, cab + a[i], i + 1)) return true;
            v[i] = 0;
            fail = a[i];
            if (!cab || cab + a[i] == len) return false;
        }
    }
    return false;
}

int main() {
    while (scanf("%d", &n), n) {
        int sum = 0, maxv = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            maxv = std::max(maxv, a[i]);
            sum += a[i];
        }
        std::sort(a, a + n, std::greater<int>());
        for (len = maxv; len <= sum; ++len) {
            if (sum % len) continue;
            cnt = sum / len;
            memset(v, 0, sizeof(v));
            if (dfs(0, 0, 0)) break;
        }
        std::cout << len << std::endl;
    }
    return 0;
}