#include <iostream>

int n;
const int N = 25e4 + 10;
long long a[N], tmp[N];

long long merge_sort(long long *a, int l, int r) {
    if (l >= r) {
        return 0;
    }
    int mid = l + r >> 1;
    long long res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    int i = l, j = mid + 1;
    int k = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else res += mid - i + 1, tmp[k++] = a[j++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int i = l, j = 0; i <= r; ++i, ++j) {
        a[i] = tmp[j];
    }
    return res;
}

int main() {
    int x = 0, cnt = 0;
    while (std::cin >> n) {
        cnt = 0;
        for (int i = 0; i < n * n; ++i) {
            std::cin >> x;
            if (x) {
                a[cnt++] = x;
            }
        }
        long long res1 = merge_sort(a, 0, cnt - 1);
        cnt = 0;
        for (int i = 0; i < n * n; ++i) {
            std::cin >> x;
            if (x) {
                a[cnt++] = x;
            }
        }
        long long res2 = merge_sort(a, 0, cnt - 1);
        if ((res1 & 1) - (res2 & 1) == 0) {
            std::cout << "TAK" << std::endl;
        }
        else {
            std::cout << "NIE" << std::endl;
        }
    }

    return 0;
}