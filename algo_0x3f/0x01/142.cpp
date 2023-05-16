#include <iostream>
#include <cstring>

int n, m;
const int N = 1e6 + 10, M = 3e6 + 10;
char s[N];
int idx, trie[M][26], cnt[M];

void insert(char *s) {
    int p = 0;
    for (int i = 0; i < strlen(s); ++i) {
        int u = s[i] - 'a';
        if (!trie[p][u]) trie[p][u] = ++idx; 
        p = trie[p][u];
    }
    ++cnt[p];
}

int search(char *s) {
    int p = 0, res = 0;
    for (int i = 0; i < strlen(s); ++i) {
        int u = s[i] - 'a';
        if (!trie[p][u]) break;
        p = trie[p][u];
        res += cnt[p];
    }
    return res;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        insert(s);
    }
    while (m--) {
        std::cin >> s;
        int res = search(s);
        std::cout << res << std::endl;
    }

    return 0;
}