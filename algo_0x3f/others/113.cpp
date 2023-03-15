// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> res;
        res.push_back(1);

        for (int i = 2; i <= N; ++i) {
            // 找到右边界极大值点target(i)的位置
            int l = 0, r = res.size() - 1;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (compare(res[mid], i)) {
                    l = mid;
                }
                else {
                    r = mid - 1;
                }            
            }
            res.push_back(i);
            // 插入排序
            for (int j = res.size() - 2; j > l; --j) {
                swap(res[j], res[j + 1]);
            }
            // 如果所有数都大于i
            if (compare(i, res[l])) {
                swap(res[l], res[l + 1]);
            }
        }
        return res;
    }
};