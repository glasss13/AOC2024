#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

constexpr array<pair<int, int>, 4> mapping = {
    {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

set<pair<int, int>> get_seen(const vector<string>& lines, int row, int col) {
    int dir_idx = 0;
    set<pair<int, int>> seen;

    while (true) {
        seen.emplace(row, col);
        int next_row = row + mapping[dir_idx].first;
        int next_col = col + mapping[dir_idx].second;

        if (next_row < 0 || next_row >= lines.size() || next_col < 0 ||
            next_col >= lines[0].size()) {
            break;
        }

        if (lines[next_row][next_col] == '#') {
            dir_idx = (dir_idx + 1) % 4;
        } else {
            row = next_row;
            col = next_col;
        }
    }
    return seen;
}

int part1(vector<string> lines) {
    int dir_idx = 0;

    int row, col;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].size(); ++j) {
            if (lines[i][j] == '^') {
                row = i;
                col = j;
            }
        }
    }

    return get_seen(lines, row, col).size();
}

bool infinite_loop(const vector<string>& lines, int row, int col,
                   int direction) {
    // array<array<char, 130>, 130> seen{};
    vector<vector<char>> seen(lines.size(), vector<char>(lines[0].size(), 0));

    while (true) {
        if (seen[row][col] & (1 << direction)) {
            return true;
        }
        seen[row][col] |= (1 << direction);
        int next_row = row + mapping[direction].first;
        int next_col = col + mapping[direction].second;

        if (next_row < 0 || next_row >= lines.size() || next_col < 0 ||
            next_col >= lines[0].size()) {
            return false;
        }

        if (lines[next_row][next_col] == '#') {
            direction = (direction + 1) % 4;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return false;
}

int part2(vector<string> lines) {
    int direction = 0;

    int row, col;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].size(); ++j) {
            if (lines[i][j] == '^') {
                row = i;
                col = j;
            }
        }
    }

    auto seen = get_seen(lines, row, col);

    int ret = 0;
    for (auto [i, j] : seen) {
        if (lines[i][j] == '.') {
            vector<string> cp = lines;
            cp[i][j] = '#';
            ret += infinite_loop(cp, row, col, direction);
        }
    }

    return ret;
}

int main() {
    ifstream file("inputs/day6.txt");

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
