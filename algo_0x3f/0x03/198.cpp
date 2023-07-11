#include <iostream>
#include <cstring>

// 指数之和<=30
// 最多十个不同质因子，指数依次递减
// 最多指数的最小的
int n;
int primes[10]= {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int minp; // 反素数
int maxd; // 最大约数个数

// 第几个质数 上一个指数 数的乘积 约数个数
void dfs(int u, int last, int p, int s) {
    if (s > maxd || s == maxd && p < minp) {
        maxd = s;
        minp = p;
    }
    if (u == 9) return;
    for (int i = 1; i <= last; ++i) {
        if ((long long)p * primes[u] > n) break;
        p *= primes[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}

int main() {
    std::cin >> n;
    dfs(0, 30, 1, 1);
    std::cout << minp << std::endl;
    return 0;
}