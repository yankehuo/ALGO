#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using std::vector;
using LL = long long;
using PII = std::pair<int, int>;
const int MOD = 9901;
int a, b;
vector<PII> pri;

void decompose(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                ++cnt;
                x /= i;
            }
            pri.push_back({i, cnt});
        }
    }
    if (x != 1) {
        pri.push_back({x, 1});
    }
}

int qmi(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
    }
    return res;
}

int sum(int p, int c) {
    if (p == 0) return 0;
    if (c == 0) return 1;
    if (c & 1) {
        return ((1 + qmi(p, (c + 1) / 2)) * sum(p, (c - 1) / 2)) % MOD;
    }
    else {
        return (1 + qmi(p, c / 2)) * sum(p, c / 2 - 1) % MOD + qmi(p, c) % MOD;
    }
}

int calc(int p, int c) {
    int res = 0;
    if ((p - 1) % MOD == 0) {
        res = (c + 1) % MOD;
    }
    else {
        res = (qmi(p, c + 1) - 1) % MOD * qmi(p - 1, MOD - 2) % MOD;
    }
    return res;
}

int main() {
    std::cin >> a >> b;
    decompose(a);
    int res = 1;
    for (int i = 0; i < pri.size(); ++i) {
        int prime = pri[i].first, cnt = pri[i].second;
        // res = (LL)res * sum(prime, b * cnt) % MOD;
        res = (LL)res * calc(prime, b * cnt) % MOD;
    }
    printf("%d\n", res);

    return res;
}