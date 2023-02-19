#include <iostream>
#include <vector>

using namespace std;
using PII = pair<int, int>;
int a, b;
int MOD = 9901;
vector<PII> vec;

void divide(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i;
                ++cnt;
            }
            vec.emplace_back(i, cnt);
        }
    }
    if (x != 1) {
        vec.emplace_back(x, 1);
    }
}

int qmi(int p, int k) {
    int res = 1;
    for (; k; k >>= 1) {
        if (k & 1) {
            res = res * p % MOD;
        }
        p = p * p % MOD;
    }
    return res;
}

int sum(int p, int k) {
    if (k == 0) {
        return 1;
    }
    if (p == 0) {
        return 0;
    }
    if (k & 1) {
        return (1 + qmi(p, (k + 1) / 2)) * sum(p, (k - 1) / 2) % MOD;
    }
    return (1 + qmi(p, k / 2)) * sum(p, k / 2 - 1) % MOD + qmi(p, k) % MOD;
}

int main() {
    cin >> a >> b;
    divide(a);
    int res = 1;
    for (auto &t : vec) {
        int p = t.first, k = t.second;
        res = res * sum(p, b * k) % MOD;
    }
    cout << res << endl;
    
    return 0;
}