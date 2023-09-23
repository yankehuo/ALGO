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
    int n;
    std::cin >> n;
    LL a1, m1;
    std::cin >> a1 >> m1;
    bool flag = true;
    LL a2, m2;
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> a2 >> m2;
        LL k1, k2;
        LL d = extgcd(a1, a2, k1, k2);
        if ((m2 - m1) % d) {
            flag = false;
            break;
        }
        k1 *= (m2 - m1) / d;
        LL t = a2 / d;
        k1 = (k1 % t + t) % t;

        m1 = m1 + a1 * k1;
        a1 = std::abs(a1 / d * a2); // note
    }
    if (flag) std::cout << (m1 % a1 + a1) % a1 << std::endl;
    else puts("-1");

    return 0;
}