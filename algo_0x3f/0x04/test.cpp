#include <iostream>
#include <vector>
#include <cstring>

using std::vector;
int arr[5] = {0, 1, 2, 3, 4};

void test(int x) {
    printf("x:%d\n", x);
}

int main() {
    // vector<int> factor[5000];
    // int n = 20;
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n / i; ++j) {
    //         factor[i * j].push_back(i);
    //     }
    // }
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 0; j < factor[i].size(); ++j) {
    //         printf("%d ", factor[i][j]);
    //     }
    //     puts("");
    // }
    int i = 0;
    // first test(arr[i])), then ++i
    test(arr[i++]);
    test(arr[++i]);
    return 0;
}