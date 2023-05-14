#include <iostream>
#include <algorithm>
#include <climits>

using PII = std::pair<int, int>;
int n;
const int N = 2e5 + 10;
PII arr[N];

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].first;
        arr[i].second = i;
    }
    std::sort(arr, arr + n);
    int pre = INT_MAX, cnt = 1, dir = -1;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && arr[i].first == arr[j].first) ++j;
        int minp = arr[i].second, maxp = arr[j - 1].second;
        if (dir == -1) {
            if (pre > maxp) {
                pre = minp;
            }
            else {
                dir = 1;
                pre = maxp;
            }
        }
        else {
            if (pre < minp) {
                pre = maxp;
            }
            else {
                dir = -1;
                ++cnt;
                pre = minp;
            }
        }
        i = j;
    }
    std::cout << cnt << std::endl;

    return 0;
}
