#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
vector<char> ops;
vector<int> nums;
unordered_map<char, int> grade{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};

int qmi(int a, int b) {
    int res = 0;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a;
        a = a * a;
    }
    return res;
}

void eval() {
    int y = nums.back(); nums.pop_back();
    int x = nums.back(); nums.pop_back();
    char op = ops.back(); ops.pop_back();
    int z = 0;
    switch (op) {
        case '+':
            z = x + y;
            break;
        case '-':
                z = x - y;
                break;
        case '*':
            z = x * y;
            break;
        case '/':
            z = x / y;
            break;
        case '^':
            z = qmi(x, y);
            break;
    }
    nums.push_back(z);
}

int main() {
    string s;
    cin >> s;
    int left_bracket = 0, right_bracket = 0;
    for (const auto &ch : s) {
        if (ch == '(') ++left_bracket;
        else if (ch == ')') ++right_bracket;
    }
    int diff = abs(left_bracket - right_bracket);
    if (left_bracket <= right_bracket) s = string(diff, '(') + s;
    else s = s + string(diff, ')');
    for (int i = 0; i < s.size(); ++i) {
        if (i > 0 && s[i] == '-' && s[i - 1] == '(') {
            s.insert(i, "0");
        }
    }
    for (int i = 0; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            int t = 0;
            while (i < s.size() && isdigit(s[i])) {
                t = t * 10 + s[i] - '0';
                ++i;
            }
            nums.push_back(t);
            i = i - 1;
        }
        else if (s[i] == '(') {
            ops.push_back('(');
        }
        else if (s[i] == ')') {
            while (ops.size() && ops.back() != '(') {
                eval();
            }
            if (ops.size()) ops.pop_back();
        }
        else {
            while (ops.size() && grade[s[i]] <= grade[ops.back()]) {
                eval();
            }
            ops.push_back(s[i]);
        }
    }
    while (ops.size()) {
        eval();
    }
    cout << nums.back() << endl;
    return 0;

}