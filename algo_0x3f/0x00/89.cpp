#include <iostream>
static int a, b, p;

// b: ck ck-1 ... c0
int qmi(long long a, long long b, long long c) {
    long long res = 1 % p;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
    }
    return res;
}

int main() {
    std::cin >> a >> b >> p;
    std::cout << qmi(a, b, p) << std::endl;

    return 0;
}