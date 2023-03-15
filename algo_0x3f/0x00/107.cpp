#include <iostream>

const int N = 5e5 + 10;
long long a[N], b[N];
long long cnt;
long long tmp[N];
int n;

void calc(long long *arr, int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    calc(arr, l, mid);
    calc(arr, mid + 1, r);
    for (int k = l; k <= r; ++k) {
        b[k] = a[k];
    }
    int i = l, j = mid + 1;
    for (int k = l; k <= r; ++k) {
        if (i == mid + 1) {
            a[k] = b[j++];
        }
        else if (j == r + 1) {
            a[k] = b[i++];
        }
        else if (b[i] <= b[j]) {
            a[k] = b[i++];
        }
        else {
            cnt += mid - i + 1;
            a[k] = b[j++];
        }
    }
}

long long merge_sort(long long *a, int l, int r) {
    if (l >= r) {
        return 0;
    }
    int mid = l + r >> 1;
    long long res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i];
        else res += mid - i + 1, tmp[k++] = a[j];
    }
    while (i <= mid) tmp[k++] = a[i];
    while (j <= r) tmp[k++] = a[j];
    for (int i = l, j = 0; i <= r; ++i, ++j) {
        a[i] = tmp[j];
    }
    return res;
}

int main() {
    while (std::cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        cnt = 0;
        calc(a, 0, n - 1);
        std::cout << cnt << std::endl;
    }
    return 0;
}