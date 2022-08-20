#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
const double eps = 1e-6;
int n, f;
double a[N], s[N];
double avg;

// 二分
// 公式推出来
// 长度至少为f的最大连续线段和（前缀和+推公式）

bool check(double avg) {
    memset(s, 0, sizeof s);  
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + a[i] - avg;
    }
    double minVal = 1e6;
    for (int i = f; i <= n; ++i) {
        minVal = min(minVal, s[i - f]);
        if (s[i] - minVal >= 0) return true;
    }
    return false;
}

int main() {
    cin >> n >> f;
    double minVal = 2000, maxVal = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        minVal = min(minVal, a[i]);
        maxVal = max(maxVal, a[i]);
    }
    double l = minVal, r = maxVal;
    while (l + eps < r) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    int res = static_cast<int>(r * 1000);
    cout << res << endl;
    
    return 0;
}
