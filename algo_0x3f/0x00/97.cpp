#include <iostream>
#include <vector>

// sum(p, c) calc one by dfs sum(p, c/2)
// calc 1+p+p^2+...p^c
// 约数之和是质因子乘积(1+p+p^2+p^3+...p^c)*(1+p+p^2+...p^c2)
using PII = std::pair<int, int>;
int a, b;
const int MOD = 9901;
std::vector<PII> primeCnt;

void decompose(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                ++cnt;
                x /= i;
            }
            primeCnt.emplace_back(i, cnt);
        }
    }
    if (x != 1) {
        primeCnt.emplace_back(x, 1);
    }
}

int qmi(int a, int b) {
    a = a % MOD;
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
    if (p == 0) {
        return 0;
    }
    if (c == 0) {
        return 1;
    }
    if (c & 1) {
        return (1 + qmi(p, (c + 1) / 2)) * sum(p, (c - 1) / 2) % MOD;
    }
    else {
        return ((1 + qmi(p, c / 2)) * sum(p, c / 2 - 1) + qmi(p, c)) % MOD;
    }
}

int main() {
    std::cin >> a >> b;
    int res = 1;
    // 分解质因数
    decompose(a);

    for (int i = 0; i < primeCnt.size(); ++i) {
        int prime = primeCnt[i].first, cnt = primeCnt[i].second;
        res = res * sum(prime, b * cnt) % MOD;
    }
    std::cout << res << std::endl;

    return 0;
}