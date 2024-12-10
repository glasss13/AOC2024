#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

vector<vector<int>> parse_input(vector<string> lines) {
    vector<vector<int>> out;
    int n = lines.size();
    int m = lines[0].size();

    for (int i = 0; i < n; ++i) {
        vector<int> x;
        for (int j = 0; j < m; ++j) {
            x.push_back(lines[i][j] - '0');
        }
        out.push_back(std::move(x));
    }

    return out;
}

void dfs(const vector<vector<int>>& g, int i, int j, int want,
         set<pair<int, int>>& pos) {
    if (i < 0 || i >= g.size() || j < 0 || j >= g[0].size()) {
        return;
    }

    if (g[i][j] != want) {
        return;
    }

    if (want == 9) {
        pos.emplace(i, j);
        return;
    }

    for (auto [dx, dy] : DIRS) {
        dfs(g, i + dx, j + dy, want + 1, pos);
    }
}

ll part1(vector<string> lines) {
    auto inp = parse_input(lines);
    ll res = 0;

    for (int i = 0; i < inp.size(); ++i) {
        for (int j = 0; j < inp[0].size(); ++j) {
            if (inp[i][j] == 0) {
                set<pair<int, int>> visited;
                dfs(inp, i, j, 0, visited);
                res += visited.size();
            }
        }
    }

    return res;
}

ll dfs2(const vector<vector<int>>& g, int i, int j, int search) {
    if (i < 0 || j < 0 || i >= g.size() || j >= g[0].size()) {
        return 0;
    }

    if (g[i][j] != search) {
        return 0;
    }

    if (search == 9) {
        return 1;
    }

    ll res = 0;
    for (auto [dx, dy] : DIRS) {
        res += dfs2(g, i + dx, j + dy, search + 1);
    }

    return res;
}

ll part2(vector<string> lines) {
    auto inp = parse_input(lines);

    ll res = 0;
    for (int i = 0; i < inp.size(); ++i) {
        for (int j = 0; j < inp[0].size(); ++j) {
            if (inp[i][j] == 0) {
                res += dfs2(inp, i, j, 0);
            }
        }
    }

    return res;
}

int main() {
    ifstream file("inputs/day10.txt");

    string line;
    vector<string> lines;
    string full_input;
    while (std::getline(file, line)) {
        lines.push_back(line);
        full_input += line;
    }

    auto p1_start = chrono::high_resolution_clock::now();
    auto p1 = part1(lines);
    auto p2_start = chrono::high_resolution_clock::now();
    auto p2 = part2(lines);
    auto p2_end = chrono::high_resolution_clock::now();
    cout << "part1: " << p1 << '\n';
    cout << "part2: " << p2 << '\n';

    auto p1_time =
        chrono::duration_cast<chrono::microseconds>(p2_start - p1_start);
    auto p2_time =
        chrono::duration_cast<chrono::microseconds>(p2_end - p2_start);
    cout << "part1(µs): " << p1_time.count() << '\n';
    cout << "part2(µs): " << p2_time.count() << '\n';
}
