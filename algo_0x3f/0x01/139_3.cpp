#include <iostream>
#include <cstring>
#include <cstring>

const int N = 2e6 + 10;
char s[N];
int p[N];

int main() {
    int cnt = 0;
    while(std::cin >> s + 1, strcmp(s + 1, "END")) {
        int n = strlen(s + 1) * 2;
        for (int i = n; i > 0; i -= 2) {
            s[i] = s[i / 2];
            s[i - 1] = 'z' + 1;
        }
        s[0] = '^';
        s[++n] = 'z' + 1;
        int mx = 0, id = 0, res = 0;
        memset(p, 0, sizeof(p));
        for (int i = 1; i <= n; ++i) {
            if (mx > i) {
                p[i] = std::min(mx - i, p[2 * id - i]);
            }
            else {
                p[i] = 1;
            }
            while (s[i - p[i]] == s[i + p[i]]) ++p[i];
            if (p[i] + i > mx) {
                mx = p[i] + i;
                id = i;
            }
            res = std::max(res, p[i]);
            // std::cout << i << ", " << s[i] << ", " << p[i] << "; ";
        }

        printf("Case %d: %d\n", ++cnt, res - 1);
    }
    return 0;
}