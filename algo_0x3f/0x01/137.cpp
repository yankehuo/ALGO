#include <iostream>
#include <algorithm>
#include <cstring>

int n;
const int N = 1e5 + 10;
const int P = 99991;
int snow[N][6], h[N], ne[N];
int idx = 0;

int H(int *a) {
    int sum = 0, mul = 1;
    for (int i = 0; i < 6; ++i) {
        sum = (sum + a[i]) % P;
        mul = (long long) mul * a[i] % P;
    }
    return (sum + mul) % P;
}

bool equal(int *a, int *b) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            bool eq = 1;
            for (int k = 0; k < 6; ++k) {
                if (a[(i + k) % 6] != b[(j + k) % 6]) {
                    eq = 0;
                }
            }
            if (eq) {
                return 1;
            }
            eq = 1;
            for (int k = 0; k < 6; ++k) {
                if (a[(i + k) % 6] != b[(j - k + 6) % 6]) {
                    eq = 0;
                }
            }
            if (eq) {
                return 1;
            }
        }
    }
    return 0;
}

bool insert(int *a) {
    int val = H(a);
    for (int i = h[val]; ~i; i = ne[i]) {
        if (equal(snow[i], a)) return true;
    }
    memcpy(snow[idx], a, 6 * sizeof(int));
    ne[idx] = h[val];
    h[val] = idx++;
    return false;
}

int main() {
    std::cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; ++i) {
        int a[10];
        for (int j = 0; j < 6; ++j) {
            std::cin >> a[j];
        }
        if (insert(a)) {
            puts("Twin snowflakes found.");
            return 0;
        }
    }
    puts("No two snowflakes are alike.");

}