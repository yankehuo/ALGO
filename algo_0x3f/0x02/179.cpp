#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <queue>

int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
char ops[] = {'u', 'd', 'l', 'r'};
std::unordered_map<std::string, int> dist;
using PIS = std::pair<int, std::string>;

int f(std::string state) {
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        if (state[i] == 'x') continue;
        int t = state[i] - '1';
        res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
    }
    return res;
}

std::string a_star(std::string start) {
    std::string end = "12345678x";
    dist[start] = 0;
    std::priority_queue<PIS, std::vector<PIS>, std::greater<>> hp;
    hp.push({f(start), start});
    std::unordered_map<std::string, std::pair<char, std::string>> pre;
    while (hp.size()) {
        auto t = hp.top();
        hp.pop();
        std::string state = t.second;
        if (state == end) break;
        int x, y;
        for (int i = 0; i < 9; ++i) {
            if (state[i] == 'x') {
                x = i / 3, y = i % 3;
                break;
            }
        }
        std::string source = state;
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 0 || tx >= 3 || ty < 0 || ty >= 3) continue;
            state = source;
            std::swap(state[x * 3 + y], state[tx * 3 + ty]);
            if (!dist.count(state) || dist[state] > dist[source] + 1) {
                dist[state] = dist[source] + 1;
                hp.push({f(state) + dist[state], state});
                pre[state] = {ops[i], source};
            }
        }
    }
    std::string res;
    while (end != start) {
        res += pre[end].first;
        end = pre[end].second;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    std::string str, seq;
    int cnt = 0;
    char ch;
    while (std::cin >> ch) {
        str += ch;
        if (ch != 'x') seq += ch;
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            if (seq[i] > seq[j]) ++cnt;
        }
    }
    if (cnt & 1) puts("unsolvable");
    else std::cout << a_star(str) << std::endl;

    return 0;
}