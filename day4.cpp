#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

int bfs(const vector<string>& data, int i, int j, int xmas_idx, int dir_idx) {
    if (i < 0 || j < 0 || i >= data.size() || j >= data[i].size()) {
        return 0;
    }

    if ("XMAS"sv[xmas_idx] != data[i][j]) {
        return 0;
    }

    if (xmas_idx == "XMAS"sv.size() - 1) {
        return 1;
    }

    return bfs(data, i + ALL_DIRS[dir_idx].first, j + ALL_DIRS[dir_idx].second,
               xmas_idx + 1, dir_idx);
}

int part1(vector<string> lines) {
    int res = 0;

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            for (int dir = 0; dir < ALL_DIRS.size(); ++dir) {
                res += bfs(lines, i, j, 0, dir);
            }
        }
    }

    return res;
}

bool part2_check(const vector<string>& data, int i, int j) {
    if (i - 1 < 0 || j - 1 < 0 || i + 1 >= data.size() ||
        j + 1 >= data[i].size()) {
        return false;
    }

    if (data[i][j] != 'A') return false;

    unordered_set<char> good_chars = {'S', 'M'};

    if (data[i + 1][j + 1] != data[i - 1][j - 1] &&
        good_chars.contains(data[i + 1][j + 1]) &&
        good_chars.contains(data[i - 1][j - 1])) {
        if (data[i + 1][j - 1] != data[i - 1][j + 1] &&
            good_chars.contains(data[i + 1][j - 1]) &&
            good_chars.contains(data[i - 1][j + 1])) {
            return true;
        }
    }

    return false;
}

int part2(vector<string> lines) {
    int ret = 0;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].size(); ++j) {
            ret += static_cast<int>(part2_check(lines, i, j));
        }
    }

    return ret;
}

int main() {
    ifstream file("inputs/day4.txt");

    string line;
    vector<string> lines;
    string full_input;
    while (std::getline(file, line)) {
        lines.push_back(line);
        full_input += line;
    }

    cout << "part1: " << part1(lines) << '\n';
    cout << "part2: " << part2(lines) << '\n';
}
