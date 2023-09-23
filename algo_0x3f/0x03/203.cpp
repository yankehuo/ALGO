#include <iostream>
#include <cstring>

using LL = long long;

LL extgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    LL d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    LL a, b;
    std::cin >> a >> b;
    LL x = 0, y = 0;
    extgcd(a, b, x, y);
    std::cout << (x % b + b) % b << std::endl;

    return 0;
}