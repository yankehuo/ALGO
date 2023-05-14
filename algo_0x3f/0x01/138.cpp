#include <iostream>
#include <cstring>

const int P = 131; // 13331
const int N = 1e6 + 10;
char s[N];
int m;
int h[N], p[N];

int main() {
    const char *t1 = "hello!";
    std::cout << strlen(t1) << " "  << strlen(t1 + 1) << std::endl;
    std::cin >> s + 1;
    int len = strlen(s + 1);
    p[0] = 1;
    for (int i = 1; i <= len; ++i) {
        h[i] = h[i - 1] * P + (s[i] - 'a' + 1);
        p[i] = p[i - 1] * P;
    }
    std::cin >> m;
    int l1, r1, l2, r2;
    while (m--) {
        std::cin >> l1 >> r1 >> l2 >> r2;
        if (h[r1] - h[l1 - 1] * p[r1 - l1 + 1] == h[r2] - h[l2 - 1] * p[r2 - l2 + 1]) {
           puts("Yes");
        }
        else {
            puts("No");
        }
    }

    return 0;
}