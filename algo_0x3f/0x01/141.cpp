#include <iostream>
#include <cstring>

const int N = 1e6 + 10;
char a[N];
int n, ne[N], cnt;

/*
next[1] = 0;
for (int i = 2, j = 0; i <= n; ++i） {
    while (j > 0 && a[i] != a[j + 1]) j = next[j];
    if (a[i] == a[j + 1]) ++j;
    next[i] = j;
}

for (int i = 1, j = 0; i <= m; ++i) {
    while (j > 0 && (j == n || b[i] != a[j + 1])) j = next[j];
    if (b[i] == a[j + 1]) ++j;
    f[i] = j;
}
*/

void get_next() {
    ne[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j > 0 && a[i] != a[j + 1]) j = ne[j];
        if (a[i] == a[j + 1]) ++j;
        ne[i] = j;
    }
}

int main() {
    while (scanf("%d", &n), n) {
        printf("Test case #%d\n", ++cnt);
        scanf("%s", a + 1);
        get_next();
        for (int i = 2; i <= n; ++i) {
            if (ne[i] > 0 && i % (i - ne[i]) == 0) {
                printf("%d %d\n", i, i / (i - ne[i]));
            }
        }
        puts("");
    }
    return 0;
}