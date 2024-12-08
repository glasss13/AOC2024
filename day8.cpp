#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

unordered_map<char, vector<pair<int, int>>> parse_input(
    const vector<string>& lines) {
    unordered_map<char, vector<pair<int, int>>> out;

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].size(); ++j) {
            if (lines[i][j] != '.') {
                out[lines[i][j]].emplace_back(i, j);
            }
        }
    }

    return out;
}

ll part1(vector<string> lines) {
    auto inp = parse_input(lines);

    auto in_grid_r = [&](int idx) { return idx < lines.size() && idx >= 0; };
    auto in_grid_c = [&](int idx) { return idx < lines[0].size() && idx >= 0; };

    set<pair<int, int>> antinode_points;

    for (const auto& [_, positions] : inp) {
        for (int i = 0; i < positions.size(); ++i) {
            for (int j = 0; j < positions.size(); ++j) {
                if (i == j) continue;

                auto [r_1, c_1] = positions[i];
                auto [r_2, c_2] = positions[j];

                int delta_r = r_1 - r_2;
                int delta_c = c_1 - c_2;

                if (in_grid_r(r_1 + delta_r) && in_grid_c(c_1 + delta_c)) {
                    antinode_points.emplace(r_1 + delta_r, c_1 + delta_c);
                }
            }
        }
    }

    return antinode_points.size();
}

ll part2(vector<string> lines) {
    auto inp = parse_input(lines);

    auto in_grid_r = [&](int idx) { return idx < lines.size() && idx >= 0; };
    auto in_grid_c = [&](int idx) { return idx < lines[0].size() && idx >= 0; };

    set<pair<int, int>> antinode_points;

    for (const auto& [_, positions] : inp) {
        for (int i = 0; i < positions.size(); ++i) {
            for (int j = 0; j < positions.size(); ++j) {
                if (i == j) continue;

                auto [r_1, c_1] = positions[i];
                auto [r_2, c_2] = positions[j];

                int delta_r = r_1 - r_2;
                int delta_c = c_1 - c_2;
                while (in_grid_r(r_1) && in_grid_c(c_1)) {
                    antinode_points.emplace(r_1, c_1);

                    r_1 += delta_r;
                    c_1 += delta_c;
                }
            }
        }
    }

    return antinode_points.size();
}

int main() {
    ifstream file("inputs/day8.txt");

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
