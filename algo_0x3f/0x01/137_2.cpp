#include <iostream>
#include <cstring>
#include <algorithm>

int n;
const int N = 1e5 + 10;
int snows[N][6], idx[N];

void get_min(int *b) {
    static int a[12];
    for (int i = 0; i < 12; ++i) a[i] = b[i % 6];
    int i = 0, j = 1, k = 0;
    while (i < 6 && j < 6) {
        for (k = 0; k < 6 && a[i + k] == a[j + k]; ++k) ;
        if (k == 6) break;
        if (a[i + k] > a[j + k]) {
            i += k + 1;
            if (i == j) ++i;
        }
        else {
            j += k + 1;
            if (i == j) ++j;
        }
    }
    k = std::min(i, j);
    for (i = 0; i < 6; ++i) {
        b[i] = a[i + k];
    }
}

bool cmp(int a, int b) {
    for (int i = 0; i < 6; ++i) {
        if (snows[a][i] < snows[b][i]) {
            return true;
        }
        else if (snows[a][i] > snows[b][i]) {
            return false;
        }
    }
    return false;
}

bool cmp2(int a[], int b[]) {
    for (int i = 0; i < 6; ++i) {
        if (a[i] < b[i]) return true;
        else if (a[i] > b[i]) return false;
    }
    return false;
}

int main() {
    std::cin >> n;
    int snow[6], isnow[6];
    for (int i = 0; i < n; ++i) {
        for (int j = 0, k = 5; j < 6; ++j, --k) {
            std::cin >> snow[j];
            isnow[k] = snow[j];
        }
        get_min(snow);
        get_min(isnow);
        if (cmp2(snow, isnow)) memcpy(snows[i], snow, sizeof snow);
        else memcpy(snows[i], isnow, sizeof isnow);
        idx[i] = i;
    }
    std::sort(idx, idx + n, cmp);
    for (int i = 1; i < n; ++i) {
        if (!cmp(idx[i], idx[i - 1]) && !cmp(idx[i - 1], idx[i])) {
            puts("Twin snowflakes found.");
            return 0;
        }
    }
    puts("No two snowflakes are alike.");
    return 0;
}