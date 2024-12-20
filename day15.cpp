#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

ll part1(vector<string> lines) {
    auto split =
        ranges::find_if(lines, [](const auto& l) { return l.empty(); });

    vector<string> grid(lines.begin(), split);
    int r, c;
    for (int i = 0; i < grid.size(); ++i) {
        if (auto j = grid[i].find('@'); j != string::npos) {
            r = i;
            c = j;
        }
    }

    string instructions;
    for (auto it = split + 1; it != lines.end(); ++it) {
        instructions += *it;
    }

    unordered_map<char, pair<int, int>> mapping = {
        {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}, {'^', {-1, 0}}};
    for (auto instr : instructions) {
        auto [dr, dc] = mapping[instr];

        int cur_r = r;
        int cur_c = c;

        while (grid[cur_r][cur_c] != '.' && grid[cur_r][cur_c] != '#') {
            cur_r += dr;
            cur_c += dc;
        }

        if (grid[cur_r][cur_c] == '.') {
            while (cur_r != r || cur_c != c) {
                swap(grid[cur_r][cur_c], grid[cur_r - dr][cur_c - dc]);
                cur_r -= dr;
                cur_c -= dc;
            }

            r += dr;
            c += dc;
        }
    }

    int res = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'O') {
                res += i * 100 + j;
            }
        }
    }

    return res;
}

bool can_move(const vector<string>& g, int row, int col, pair<int, int> dir) {
    if (g[row][col] == '.') {
        return true;
    }

    if (g[row][col] == '#') {
        return false;
    }

    int nr = row + dir.first;
    int nc = col + dir.second;

    bool move_primary = can_move(g, nr, nc, dir);
    // vert
    if (dir.first != 0) {
        if (g[nr][nc] == ']') {
            return move_primary && can_move(g, nr, nc - 1, dir);
        } else if (g[nr][nc] == '[') {
            return move_primary && can_move(g, nr, nc + 1, dir);
        }
    }

    return move_primary;
}

void execute_move(vector<string>& g, int row, int col, pair<int, int> dir) {
    if (g[row][col] == '.' || g[row][col] == '#') {
        return;
    }

    int nr = row + dir.first;
    int nc = col + dir.second;

    // vert
    if (dir.first != 0) {
        if (g[nr][nc] == ']') {
            execute_move(g, nr, col - 1, dir);
        } else if (g[nr][nc] == '[') {
            execute_move(g, nr, col + 1, dir);
        }
    }
    execute_move(g, nr, nc, dir);

    g[nr][nc] = g[row][col];
    g[row][col] = '.';
}

ll part2(vector<string> lines) {
    auto split =
        ranges::find_if(lines, [](const auto& l) { return l.empty(); });

    vector<string> grid;
    for (auto it = lines.begin(); it < split; ++it) {
        string cur;
        for (char c : *it) {
            if (c == '#') {
                cur += "##";
            } else if (c == 'O') {
                cur += "[]";
            } else if (c == '.') {
                cur += "..";
            } else {
                cur += "@.";
            }
        }
        grid.push_back(std::move(cur));
    }

    int r, c;
    for (int i = 0; i < grid.size(); ++i) {
        if (auto j = grid[i].find('@'); j != string::npos) {
            r = i;
            c = j;
        }
    }

    string instructions;
    for (auto it = split + 1; it != lines.end(); ++it) {
        instructions += *it;
    }

    unordered_map<char, pair<int, int>> mapping = {
        {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}, {'^', {-1, 0}}};
    for (auto instr : instructions) {
        auto [dr, dc] = mapping[instr];

        if (can_move(grid, r, c, mapping[instr])) {
            execute_move(grid, r, c, mapping[instr]);
            r += dr;
            c += dc;
        }
    }

    int res = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '[') {
                res += i * 100 + j;
            }
        }
    }

    return res;
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day15.txt") : ifstream("sample.txt");

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
