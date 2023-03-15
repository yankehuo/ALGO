#include <iostream>
#include <vector>
#include <algorithm>

using PII = std::pair<int, int>;
const int N = 1010;
PII coins[N];
int n;

std::vector<int> maxVector(std::vector<int> A, std::vector<int> B) {
    if (A.size() > B.size()) {
        return A;
    }
    if (B.size() > A.size()) {
        return B;
    }
    if (std::vector<int>(A.rbegin(), A.rend()) >= std::vector<int>(B.rbegin(), B.rend())) {
        return A;
    }
    return B;
}

// reversed order
std::vector<int> divide(std::vector<int> &A, int b) {
    int r = 0;
    std::vector<int> res;
    for (int i = A.size() - 1; i >= 0; --i) {
        r = r * 10 + A[i];
        res.push_back(r / b);
        r %= b;
    }
    std::reverse(res.begin(), res.end());
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

std::vector<int> multi(std::vector<int> &A, int b) {
    int t = 0;
    std::vector<int> res;
    for (int i = 0; i < A.size(); ++i) {
        t = t + A[i] * b;
        res.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        res.push_back(t % 10);
        t /= 10;
    }
    return res;
}

int main() {
    int a, b;
    std::cin >> n;
    for (int i = 0; i <= n; ++i) {
        std::cin >> a >> b;
        // a*b sort from small to great
        coins[i] = {a * b, a};
    }
    std::sort(coins + 1, coins + n + 1);
    
    std::vector<int> res(1, 0);
    std::vector<int> product(1, 1);
    for (int i = 0; i <= n; ++i) {
        if (i) {
            res = maxVector(res, divide(product, coins[i].first / coins[i].second));
        }
        product = multi(product, coins[i].second);
    }
    for (int i = res.size() - 1; i >= 0; --i) {
        std::cout << res[i];
    }
    std::cout << std::endl;
    return 0;
}