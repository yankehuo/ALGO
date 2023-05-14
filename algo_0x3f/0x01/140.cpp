#include <iostream>
#include <algorithm>
#include <cstring>

using ULL = unsigned long long;
const int N = 3e5 + 10, P = 13331;
ULL h[N], p[N];
char str[N];
int sa[N];
int n;

ULL gethash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int get_comm_pre(int a, int b) {
    int l = 0, r = std::min(n - a + 1, n - b + 1);
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (gethash(a, a + mid - 1) == gethash(b, b + mid - 1)) {
            l = mid;
        }
        else {
            r = mid - 1;
        }
    }
    return l;
}

bool cmp(int a, int b) {
    int len = get_comm_pre(a, b);
    int av = a + len > n ? INT_MIN : str[a + len];
    int bv = b + len > n ? INT_MIN : str[b + len];
    return av < bv;
}

int main() {
    std::cin >> str + 1;
    n = strlen(str + 1);
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] * P + str[i] - 'a' + 1;
        p[i] = p[i - 1] * P;
        sa[i] = i;
    }
    std::sort(sa + 1, sa + n + 1, cmp);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", sa[i] - 1);
    }
    puts("");
    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            printf("0 ");
        }
        else {
            printf("%d ", get_comm_pre(sa[i - 1], sa[i]));
        }
    }
    puts("");
    // std::cout << sizeof (long long) << std::endl;
    return 0;
}
