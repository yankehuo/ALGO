#include <iostream>
using namespace std;
int n;

void divide(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) x /= i, ++cnt;
            cout << i << ' ' << cnt << endl;
        }
    }
    if (x > 1) cout << x << ' ' << "1" << endl;
    cout << endl;
}

int main() {
    cin >> n;
    int x;
    while (n--) {
        cin >> x;
        divide(x);
    }
    
    return 0;
}