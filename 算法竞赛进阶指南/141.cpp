#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e6 + 10;
char p[N];
int n;
int ne[N];
int cnt;

void get_next() {
    memset(ne, 0, sizeof ne);
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) ++j;
        ne[i] = j;
    }
}

int main() {
    while (scanf("%d", &n), n) {
        printf("Test case #%d\n", ++cnt);
        scanf("%s", p + 1);
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