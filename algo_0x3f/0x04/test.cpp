#include <iostream>
#include <vector>
#include <cstring>

using std::vector;

int main() {
    vector<int> factor[5000];
    int n = 20;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n / i; ++j) {
            factor[i * j].push_back(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < factor[i].size(); ++j) {
            printf("%d ", factor[i][j]);
        }
        puts("");
    }

    return 0;
}