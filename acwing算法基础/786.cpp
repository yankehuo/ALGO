#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N];
int n, k;

int quick_sort(int a[], int l, int r, int k) {
    if (l >= r) return a[k];
    int i = l - 1, j = r + 1, x = a[l + r >> 1];
    while (i < j) {
        while (a[++i] < x) ;
        while (a[--j] > x) ;
        if (i < j) swap(a[i], a[j]);
    }
    if (k <= j) return quick_sort(a, l, j, k);
    else return quick_sort(a, j + 1, r, k);
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int res = quick_sort(a, 0, n - 1, k - 1);
    cout << res << endl;
    
    return 0;
}