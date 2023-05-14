#include <iostream>
#include <queue>

int t;
const int N = 1e6 + 10, M = 1010;
int teamid[N];

int main() {
    int cnt = 0;
    int x = 0, id = 0, num = 0;
    std::string ops;
    while (std::cin >> t && t) {
        std::queue<int> q[M], team;
        printf("Scenario #%d\n", ++cnt);
        for (int i = 0; i < t; ++i) {
            std::cin >> num;
            while (num--) {
                std::cin >> x;
                teamid[x] = i;
            }
        }
        while (std::cin >> ops, ops != "STOP") {
            if (ops[0] == 'E') {
                std::cin >> x;
                id = teamid[x];
                if (q[id].empty()) {
                    team.push(id);
                }
                q[id].push(x);
            }
            else if (ops[0] == 'D') {
                id = team.front();
                std::cout << q[id].front() << std::endl;
                q[id].pop();
                if (q[id].empty()) {
                    team.pop();
                }
            }
        }
        std::cout << std::endl;
    }
    return 0;
}