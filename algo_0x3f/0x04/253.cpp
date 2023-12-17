#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>

const int N = 1e5 + 10;

struct Treap {
    int l, r;
    int dat, val; // rand dat for heap, val for key
    int size, cnt; // size for sum of cnt
} a[N];
int tot = 0;
int root = 0;
int n;
int INF = 0x7fffffff;

// insert remove getrankbyval getvalbyrank getpre getnext
int New(int x) {
    a[++tot].val = x;
    a[tot].dat = rand();
    a[tot].cnt = a[tot].size = 1;
    return tot;
}

void Update(int u) {
    a[u].size = a[a[u].l].size + a[a[u].r].size + a[u].cnt;
}

void Build() {
    New(-INF); // 1
    New(INF); // 2
    root = 1;
    a[1].r = 2;
    Update(root);
}

void zig(int &p) {
    int q = a[p].l;
    a[p].l = a[q].r;
    a[q].r = p;
    p = q;
    Update(a[p].r);
    Update(p);
}

void zag(int &p) {
    int q = a[p].r;
    a[p].r = a[q].l;
    a[q].l = p;
    p = q;
    Update(a[p].l);
    Update(p);
}

void Insert(int &p, int x) {
    if (p == 0) {
        p = New(x);
        return;
    }
    if (x == a[p].val) {
        ++a[p].cnt;
        Update(p);
        return;
    }
    if (x < a[p].val) {
        Insert(a[p].l, x);
        if (a[p].dat < a[a[p].l].dat) {
            zig(p);
        }
    }
    else {
        Insert(a[p].r, x);
        if (a[p].dat < a[a[p].r].dat) {
            zag(p);
        }
    }
    Update(p);
}

void Remove(int &p, int x) {
    if (p == 0) return;
    if (x == a[p].val) {
        if (a[p].cnt > 1) {
            --a[p].cnt;
            Update(p);
            return;
        }
        if (a[p].l || a[p].r) {
            if (a[p].r == 0 || a[a[p].l].dat > a[a[p].r].dat) {
                zig(p);
                Remove(a[p].r, x);
            }
            else {
                zag(p);
                Remove(a[p].l, x);
            }
            Update(p);
        }
        else {
            p = 0;
        }
        return;
    }
    x < a[p].val ? Remove(a[p].l, x) : Remove(a[p].r, x);
    Update(p);
}

int GetRankByVal(int p, int x) {
    if (p == 0) return 0;
    if (x == a[p].val) {
        return a[a[p].l].size + 1;
    }
    if (x < a[p].val) {
        return GetRankByVal(a[p].l, x);
    }
    return a[a[p].l].size + a[p].cnt + GetRankByVal(a[p].r, x);
}

int GetValByRank(int p, int rank) {
    if (p == 0) return INF;
    if (a[a[p].l].size >= rank) {
        return GetValByRank(a[p].l, rank);
    }
    if (a[a[p].l].size + a[p].cnt >= rank) {
        return a[p].val;
    }
    return GetValByRank(a[p].r, rank - a[p].cnt - a[a[p].l].size);
}

int GetPre(int x) {
    int ans = 1;
    int p = root;
    while (p) {
        if (x == a[p].val) {
            if (a[p].l > 0) {
                p = a[p].l;
                while (a[p].r > 0) {
                    p = a[p].r;
                }
                ans = p; 
            }
            break;
        }
        if (a[p].val < x && a[p].val > a[ans].val) {
            ans = p;
        }
        p = x < a[p].val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

int GetNext(int x) {
    int ans = 2;
    int p = root;
    while (p) {
        if (x == a[p].val) {
            if (a[p].r > 0) {
                p = a[p].r;
                while (a[p].l > 0) {
                    p = a[p].l;
                }
                ans = p;
            }
            break;
        }
        if (a[p].val > x && a[p].val < a[ans].val) {
            ans = p;
        }
        p = x < a[p].val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

int main() {
    Build();
    std::cin >> n;
    int op, x;
    for (int i = 0; i < n; ++i) {
        std::cin >> op >> x;
        switch (op) {
            case 1:
                Insert(root, x);
                break;
            case 2: 
                Remove(root, x);
                break;
            case 3: 
                printf("%d\n",GetRankByVal(root, x) - 1);
                break;
            case 4:
                printf("%d\n", GetValByRank(root, x + 1));
                break;
            case 5: 
                printf("%d\n", GetPre(x));
                break;
            case 6: 
                printf("%d\n", GetNext(x));
                break;
            default: ;
        }
    }
    return 0;
}