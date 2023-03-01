#include <iostream>

static long long a, b, p;
long long multi(long long a, long long b, long long p) {
    long long res = 0 % p;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = (res + a) % p;
        }
        a = a * 2 % p;
    }
    return res;
}

using ull = unsigned long long;
long long multi2(long long a, long long b, long long p) {
    a %= p, b %= p;
    long long res = 0;
    ull c = (long double)a * b / p;
    res = (a * b - c * p) % p;
    if (res < 0) {
        res += p;
    }
    return res;
}

int main() {
    std::cin >> a >> b >> p;
    std::cout << multi(a, b, p) << std::endl;
    std::cout << multi2(a, b, p) << std::endl;

    return 0;
}