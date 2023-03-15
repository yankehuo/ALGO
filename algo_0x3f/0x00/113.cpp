#include <iostream>
#include <vector>

// Forward declaration of compare API.
bool compare(int a, int b) {
    if (a < b) {
        return true;
    }
    else {
        return false;
    }
}
// return bool means whether a is less than b.
class Solution {
public:
    std::vector<int> specialSort(int N) {
        std::vector<int> res;
        res.push_back(1);
        for (int i = 2; i <= N; ++i) {
            int l = 0, r = res.size() - 1;
            while (l < r) {
                int mid = l + r + 1>> 1;
                if (compare(res[mid], i)) {
                    l = mid;
                }
                else {
                    r = mid - 1;
                }
            }
            res.push_back(i);
            for (int j = res.size() - 2; j > l; --j) {
                std::swap(res[j], res[j + 1]);
            }
            if (compare(i, res[l])) {
                std::swap(res[l], res[l + 1]);
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    auto vec = solution.specialSort(7);
    for (auto &p : vec) {
        std::cout << p << std::endl;
    }
    return 0;
}