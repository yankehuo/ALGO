#include <iostream>
#include <cstring>

const int N = 7e6 + 10;
int trie[N][2], idx;
int n;
int a[N];

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (!trie[p][u]) trie[p][u] = ++idx;
        p = trie[p][u];
    }
}

int query(int x) {
    int p = 0;
    int res = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (trie[p][!u]) res |= 1 << i, p = trie[p][!u];
        else p = trie[p][u]; 
    }
    return res;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        insert(a[i]);
    }
    int res = 0;
    for (int i = 1; i < n; ++i) {
        res = std::max(res, query(a[i]));
    }
    std::cout << res << std::endl;

    return 0;
}