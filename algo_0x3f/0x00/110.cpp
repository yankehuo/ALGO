#include <iostream>
#include <algorithm>

int c, l;
const int N = 2510;
using PII = std::pair<int, int>;
PII rangeSPF[N], spfCover[N];

int main() {
    std::cin >> c >> l;
    for (int i = 0; i < c; ++i) {
        std::cin >> rangeSPF[i].first >> rangeSPF[i].second;
    }
    for (int i = 0; i < l; ++i) {
        std::cin >> spfCover[i].first >> spfCover[i].second;
    }
    std::sort(rangeSPF, rangeSPF + c, std::greater<PII>());
    std::sort(spfCover, spfCover + l, std::greater<PII>());
    int res = 0;
    for (int i = 0; i < c; ++i) {
        int minSpf = rangeSPF[i].first, maxSpf = rangeSPF[i].second;
        for (int j = 0; j < l; ++j) {
            int &spf = spfCover[j].first; 
            int &cover = spfCover[j].second;
            if (cover != 0 && spf >= minSpf && spf <= maxSpf) {
                ++res;
                --cover;
                break;
            }
        }
    }
    std::cout << res << std::endl;

    return 0;
}