#include <iostream>
#include <vector>

using std::vector;
int n;
const int N = 1e5 + 10;
int a[N], l[N], r[N];
vector<int> stk;


int main() {
    while (std::cin >> n && n) {
        stk.clear();
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        r[n - 1] = n;
        for (int i = 0; i < n; ++i) {
            while (stk.size() && a[stk.back()] >= a[i]) {
                r[stk.back()] = i;
                stk.pop_back();
            }
            l[i] = stk.empty() ? -1 : stk.back();
            stk.push_back(i);
        }
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res = std::max(res, (r[i] - l[i] - 1) * (long long)a[i]);
        }
        std::cout << res << std::endl;
    }

    return 0;
}