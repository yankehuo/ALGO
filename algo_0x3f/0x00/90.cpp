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

int main() {
    std::cin >> a >> b >> p;
    std::cout << multi(a, b, p) << std::endl;

    return 0;
}