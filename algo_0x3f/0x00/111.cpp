#include <iostream>
#include <queue>
#include <algorithm>
// sort by start, watch the end, if exist: the start <= end, then establish new interval

using PII = std::pair<int, int>;
const int N = 5e5 + 10;
std::pair<PII, int> range[N];
int idx[N];
int n;

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> range[i].first.first >> range[i].first.second;
        range[i].second = i;
    }
    std::sort(range, range + n);
    std::priority_queue<PII, std::vector<PII>, std::greater<>> hp;
    for (int i = 0; i < n; ++i) {
        int st = range[i].first.first;
        int ed = range[i].first.second;
        int id = range[i].second;
        if (hp.empty() || st <= hp.top().first) {
            int num = hp.size() + 1;
            hp.push({ed, num});
            idx[id] = num;
        }
        else {
            int num = hp.top().second;
            hp.pop();
            hp.push({ed, num});
            idx[id] = num;
        }
    }
    std::cout << hp.size() << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << idx[i] << std::endl;
    }

    return 0;
}