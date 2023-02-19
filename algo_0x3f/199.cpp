#include <iostream>
using namespace std;
using LL = long long;

int n, k;

int main() {
    cin >> n >> k;
    LL res = n * k;
    for (int x = 1, gx; x <= n; x = gx + 1) {
        gx = k / x ? min(k / (k / x), n) : n;
        res -= (k / x) * (x + gx) * (gx - x + 1) / 2;
    }
    cout << res << endl;

    return 0;
}