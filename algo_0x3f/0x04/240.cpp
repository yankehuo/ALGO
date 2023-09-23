#include <iostream>
#include <algorithm>
#include <cstring>

const int M = 5e4 + 10, N = 3 * M; // for calc2()
int fa[N], d[N];
int n, k;
int t, x, y;

int get_1(int x) {
    if (x == fa[x]) return x;
    int u = get_1(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = u;
}

int get_2(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get_2(fa[x]);
}

void init_1() {
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
}

void init_2() {
    for (int i = 1; i <= 3 * n; ++i) {
        fa[i] = i;
    }
}


// mod3==0,self  mod3==1,eat mod3==2,eated
void calc_1() {
    int res = 0;
    while (k--) {
        std::cin >> t >> x >> y;
        if (x > n || y > n) ++res;
        else {
            int px = get_1(x), py = get_1(y);
            if (t == 1) {
                if (px == py && (d[x] - d[y]) % 3) ++res;
                else if (px != py) {
                    fa[px] = py;
                    d[px] = d[y] - d[x];
                }
            }
            else {
                if (px == py && (d[x] - d[y] - 1) % 3) ++res;
                else if (px != py) {
                    fa[px] = py;
                    d[px] = d[y] + 1 - d[x];
                }
            }
        }
    }
    printf("%d\n", res);
}

// xself xeat xeated
// yself yeat yeated
void calc_2() {
    int res = 0;
    while (k--) {
        std::cin >> t >> x >> y;
        if (x > n || y > n || (t == 2 && get_2(x) == get_2(y))) {
            ++res;
            continue;
        }
        if (t == 1 && (get_2(x) == get_2(y + n) || get_2(x + n) == get_2(y))) {
            ++res;
            continue;
        }
        if (t == 2 && (get_2(x) == get_2(y) || get_2(x) == get_2(y + n))) {
            ++res;
            continue;
        }
        if (t == 1) {
            fa[get_2(x)] = get_2(y);
            fa[get_2(x + n)] = get_2(y + n);
            fa[get_2(x + 2 * n)] = get_2(y + 2 * n);
        }
        else {
            fa[get_2(x + n)] = get_2(y);
            fa[get_2(x + 2 * n)] = get_2(y + n);
            fa[get_2(x)] = get_2(y + 2 * n);
        }
    }
    printf("%d\n", res);
}

int main() {
    std::cin >> n >> k;
    init_1();
    // init_2();
    calc_1();
    // calc_2();

    return 0;
}