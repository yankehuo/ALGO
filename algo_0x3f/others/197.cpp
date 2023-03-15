#include <iostream>
#include <cstring>

using namespace std;
const int N = 1e6 + 10;
int primes[N];
bool v[N];
int cnt;
int n;

void getPrimes(int n) {
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
    getPrimes(n);

    for (int i = 0; i < cnt; ++i) {
        int p = primes[i];
        int s = 0;
        for (int j = p; j <= n; j *= p) {
            s += n / j;
            if (j > n / p) break;
        }
        cout << p << ' ' << s << endl;
    }
    return 0;
}