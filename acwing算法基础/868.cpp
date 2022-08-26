// 埃氏筛法
#include <iostream>

using namespace std;

const int N = 1e6 + 10;
int primes[N], cnt;
bool v[N];
int n;

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (v[i]) continue;
        primes[cnt++] = i;
        for (int j = i + i; j <= n; j += i) {
            v[j] = 1;
        }
    }
}

int main() {
    cin >> n;
    get_primes(n);
    cout << cnt << endl;

    return 0;
}
// 线性筛法
#include <iostream>

using namespace std;

const int N = 1e6 + 10;
int primes[N], cnt;
bool v[N];
int n;

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    cin >> n;
    get_primes(n);
    cout << cnt << endl;

    return 0;
}
