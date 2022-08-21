#include <iostream>
using namespace std;
using LL = long long;
const int N = 1e5 + 10;
LL n, a[N], tmp[N];

LL merge_sort(LL a[], LL l, LL r) {
    if (l >= r) {
        return 0;
    }
    LL mid = l + r >> 1;
    LL res = 0;
    res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    LL i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        }
        else {
            res += mid - i + 1;
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }
    for (LL i = l, j = 0; i <= r; ++i, ++j) {
        a[i] = tmp[j];
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    LL res = merge_sort(a, 0, n - 1);
    cout << res << endl;
    
    return 0;
}

/*
#include <iostream>
using namespace std;
using LL = long long;
const int N = 1e5 + 10;
LL n, a[N], tmp[N];

LL merge_sort(LL a[], LL l, LL r) {
    if (l >= r) {
        return 0;
    }
    LL mid = l + r >> 1;
    LL res = 0;
    res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    LL i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            res += j - mid - 1;
            tmp[k++] = a[i++];
        }
        else {
            // res += mid - i + 1;
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        res += j - mid - 1;
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }
    for (LL i = l, j = 0; i <= r; ++i, ++j) {
        a[i] = tmp[j];
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    LL res = merge_sort(a, 0, n - 1);
    cout << res << endl;
    
    return 0;
}
*/