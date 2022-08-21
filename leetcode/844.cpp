class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int sn = s.size(), tn = t.size();
        // 记录含有的#数，以便后续配对消除字母
        int skipS = 0, skipT = 0;
        int i = sn - 1, j = tn - 1;
        while (true) {
            // 找到第一个不需要退格消除的字符
            while (i >= 0) {
                if (s[i] == '#') {
                    ++skipS;
                }
                else {
                    if (skipS > 0) --skipS;
                    else break;
                }
                --i;
            }
            while (j >= 0) {
                if (t[j] == '#') {
                    ++skipT;
                }
                else {
                    if (skipT > 0) --skipT;
                    else break;
                }
                --j;
            }
            if (i < 0 || j < 0) break;
            if (s[i] != t[j]) return false;
            --i, --j;
        }
        return i == -1 && j == -1;
    }
};