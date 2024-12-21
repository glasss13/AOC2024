#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

ll part1(vector<string> lines) {
    set<pair<int, int>> unsafe;

    for (int i = 0; i < 1024; ++i) {
        auto comma_pos = lines[i].find(',');
        ll x = stoll(lines[i].substr(0, comma_pos));
        ll y = stoll(lines[i].substr(comma_pos + 1));

        unsafe.insert({x, y});
    }

    queue<tuple<ll, ll, ll>> q;
    map<pair<int, int>, pair<int, int>> prev;
    map<pair<int, int>, ll> dists;

    q.emplace(0, 0, 0);

    while (!q.empty()) {
        auto [cur_x, cur_y, cur_dist] = q.front();
        q.pop();

        if (cur_x < 0 || cur_x > 70 || cur_y < 0 || cur_y > 70 ||
            unsafe.contains({cur_x, cur_y}) || dists.contains({cur_x, cur_y})) {
            continue;
        }

        dists[{cur_x, cur_y}] = cur_dist;

        for (auto [dx, dy] : DIRS) {
            q.emplace(cur_x + dx, cur_y + dy, cur_dist + 1);
        }
    }

    return dists[{70, 70}];
}

bool path_exists(const set<pair<int, int>>& unsafe) {
    queue<tuple<ll, ll, ll>> q;
    set<pair<int, int>> seen;

    q.emplace(0, 0, 0);

    while (!q.empty()) {
        auto [cur_x, cur_y, cur_dist] = q.front();
        q.pop();

        if (cur_x < 0 || cur_x > 70 || cur_y < 0 || cur_y > 70 ||
            unsafe.contains({cur_x, cur_y}) || seen.contains({cur_x, cur_y})) {
            continue;
        }

        if (cur_x == 70 && cur_y == 70) {
            return true;
        }

        seen.insert({cur_x, cur_y});

        for (auto [dx, dy] : DIRS) {
            q.emplace(cur_x + dx, cur_y + dy, cur_dist + 1);
        }
    }

    return false;
}

string part2(vector<string> lines) {
    set<pair<int, int>> unsafe;

    for (const auto& line : lines) {
        auto comma_pos = line.find(',');
        ll x = stoll(line.substr(0, comma_pos));
        ll y = stoll(line.substr(comma_pos + 1));

        unsafe.insert({x, y});

        if (!path_exists(unsafe)) {
            return line;
        }
    }

    return "not found";
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day18.txt") : ifstream("sample.txt");

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
