class Solution {
public:
    string reverseWords(string s) {
        // 两组指针：一组去掉空格传递，一组接收翻转加上空格
        int n = s.size();
        int k = 0; // (k, t)k指向单词开头，t指向单词的下一个位置
        for (int i = 0; i < n; ++i) {
            if (s[i] == ' ') continue;
            int j = i, t = k;
            while (j < n && s[j] != ' ') s[t++] = s[j++];
            reverse(s.begin() + k, s.begin() + t);
            s[t++] = ' ';
            k = t, i = j;
        }
        if (k) --k;
        s.erase(s.begin() + k, s.end());
        reverse(s.begin(), s.end());
        return s;
    }
};