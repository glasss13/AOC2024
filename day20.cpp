#include <bits/stdc++.h>

#include <sstream>

#include "utils.hpp"

using namespace std;

ll part1(vector<string> lines) {
    int rows = lines.size();
    int cols = lines[0].size();

    int start_r, start_c, end_r, end_c;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lines[i][j] == 'S') {
                start_r = i;
                start_c = j;
            } else if (lines[i][j] == 'E') {
                end_r = i;
                end_c = j;
            }
        }
    }

    map<pair<int, int>, int> dists;

    queue<tuple<int, int, int>> q;
    q.emplace(start_r, start_c, 0);

    while (!q.empty()) {
        auto [cur_r, cur_c, cur_dist] = q.front();
        q.pop();

        if (lines[cur_r][cur_c] == '#' || dists.contains({cur_r, cur_c}))
            continue;
        dists[{cur_r, cur_c}] = cur_dist;

        for (auto [dr, dc] : DIRS) {
            q.emplace(cur_r + dr, cur_c + dc, cur_dist + 1);
        }
    }

    int normal_time = dists[{end_r, end_c}];

    ll res = 0;

    for (auto [pos, dist] : dists) {
        int row = pos.first;
        int col = pos.second;
        for (auto [dr, dc] : DIRS) {
            int nr = row + dr * 2;
            int nc = col + dc * 2;
            if (dists.contains({nr, nc})) {
                res += dists[{nr, nc}] - (dist + 2) >= 100;
            }
        }
    }

    return res;
}

ll part2(vector<string> lines) {
    int rows = lines.size();
    int cols = lines[0].size();

    int start_r, start_c, end_r, end_c;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lines[i][j] == 'S') {
                start_r = i;
                start_c = j;
            } else if (lines[i][j] == 'E') {
                end_r = i;
                end_c = j;
            }
        }
    }

    map<pair<int, int>, int> dists;

    queue<tuple<int, int, int>> q;
    q.emplace(start_r, start_c, 0);

    while (!q.empty()) {
        auto [cur_r, cur_c, cur_dist] = q.front();
        q.pop();

        if (lines[cur_r][cur_c] == '#' || dists.contains({cur_r, cur_c}))
            continue;
        dists[{cur_r, cur_c}] = cur_dist;

        for (auto [dr, dc] : DIRS) {
            q.emplace(cur_r + dr, cur_c + dc, cur_dist + 1);
        }
    }

    int normal_time = dists[{end_r, end_c}];

    ll res = 0;

    unordered_map<int, int> savings;

    for (auto [pos, dist] : dists) {
        int row = pos.first;
        int col = pos.second;

        // row, col, steps
        set<tuple<int, int, int>> seen;
        set<pair<int, int>> cheat_pos;

        queue<tuple<int, int, int>> bfs;
        bfs.emplace(row, col, 0);

        while (!bfs.empty()) {
            auto [cur_r, cur_c, cur_steps] = bfs.front();
            bfs.pop();

            if (cur_steps > 20 || cur_r < 0 || cur_r >= rows || cur_c < 0 ||
                cur_c >= cols || seen.contains({cur_r, cur_c, cur_steps})) {
                continue;
            }

            seen.insert({cur_r, cur_c, cur_steps});

            if (lines[cur_r][cur_c] != '#') {
                if (dists[{cur_r, cur_c}] - (dist + cur_steps) >= 100 &&
                    !cheat_pos.contains({cur_r, cur_c})) {
                    ++res;
                    ++savings[dists[{cur_r, cur_c}] - (dist + cur_steps)];
                    cheat_pos.insert({cur_r, cur_c});
                }
            }

            for (auto [dr, dc] : DIRS) {
                bfs.emplace(cur_r + dr, cur_c + dc, cur_steps + 1);
            }
        }
    }

    return res;
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day20.txt") : ifstream("sample.txt");

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
