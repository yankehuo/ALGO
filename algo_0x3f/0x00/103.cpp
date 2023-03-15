#include <iostream>
#include <vector>
#include <algorithm>

// listen max; n: person number; m: cinema number
std::vector<int> alls, a, b, c;
int n, m;
const int N = 6e5 + 10;
int cnt[N];

int find(int x) {
    return std::lower_bound(alls.begin(), alls.end(), x) - alls.begin();
}

int main() {
    std::cin >> n;
    int x;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        a.push_back(x);
        alls.push_back(x);
    }
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> x;
        b.push_back(x);
        alls.push_back(x);
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> x;
        c.push_back(x);
        alls.push_back(x);
    }
    std::sort(alls.begin(), alls.end());
    alls.erase(std::unique(alls.begin(), alls.end()), alls.end());
    for (int i = 0; i < n; ++i) {
        int language = find(a[i]);
        ++cnt[language];
    }

    int res = 1, bmax = -1, cmax = -1;
    for (int i = 0; i < m; ++i) {
        int j = find(b[i]), k = find(c[i]);
        if (cnt[j] > bmax || cnt[j] == bmax && cnt[k] > cmax) {
            bmax = cnt[j];
            cmax = cnt[k];
            res = i + 1;
        }
    }
    std::cout << res << std::endl;

    return 0;
}