// 质因子的乘积大于2*10^9的个数小于等于10
// 质因子从小到大，次数依次递减
// 次数最大30 2*2^30>2*10^9
// N=p1^c1 * p2^c2 * p3^c3 ...
// 约数个数：（c1+1)*(c2+1)...
// 约数之和：（p1^0+p1^1+p1^2+...p1^c1）(p2^0+...+p2^c2)
// 最大的约数个数，乘积最小

#include <iostream>
#include <cstring>
using namespace std;
using LL = long long;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int sum;
LL minx;
int n;

// 第几个质因子 上一个质因子次数 当前约数乘积 当前约数个数
void dfs(int u, int last, int p, int s) {
    if (sum < s || sum == s && p < minx) {
        sum = s;
        minx = p;
    }
    if (u == 9) return;
    for (int i = 1; i <= last; ++i) {
        if ((LL)p * primes[u] > n) break;
        p *= primes[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}

int main() {
    cin >> n;
    dfs(0, 30, 1, 1);
    cout << minx << endl;

    return 0;
}