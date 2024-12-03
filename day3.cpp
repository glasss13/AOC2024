#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

vector<pair<int, int>> parse_input(string line) {
    vector<pair<int, int>> out;
    size_t idx = 0;
    while ((idx = line.find("mul("sv, idx)) != string::npos) {
        idx += "mul("sv.size();

        if (idx >= line.size()) break;

        int consumed = 0;
        int a = 0;
        while (idx < line.size() && isdigit(line[idx])) {
            ++consumed;
            a *= 10;
            a += line[idx] - '0';
            ++idx;
        }
        if (consumed > 3 || consumed == 0) continue;
        if (idx >= line.size()) continue;

        if (line[idx] != ',') continue;
        ++idx;

        consumed = 0;
        int b = 0;
        while (idx < line.size() && isdigit(line[idx])) {
            ++consumed;
            b *= 10;
            b += line[idx] - '0';
            ++idx;
        }
        if (idx >= line.size()) continue;

        if (line[idx] != ')') continue;
        out.emplace_back(a, b);
    }
    return out;
}

int part1(string line) {
    auto input = parse_input(line);

    auto stuff =
        input | views::transform([](auto p) { return p.first * p.second; });

    return ranges::fold_left(stuff, 0, plus<int>{});
}

vector<pair<int, int>> parse_input2(string line) {
    vector<pair<int, int>> out;
    size_t idx = 0;
    bool doing = true;
    while (line.find("mul("sv, idx) != string::npos ||
           line.find("do()"sv, idx) != string::npos ||
           line.find("don't()"sv, idx) != string::npos) {
        size_t mul_idx = line.find("mul("sv, idx);
        size_t do_idx = line.find("do()"sv, idx);
        size_t dont_idx = line.find("don't()"sv, idx);

        if (do_idx < mul_idx && do_idx < dont_idx) {
            doing = true;
            idx = do_idx + "do()"sv.size();
            continue;
        }
        if (dont_idx < mul_idx && dont_idx < do_idx) {
            doing = false;
            idx = dont_idx + "don't()"sv.size();
            continue;
        }

        idx = mul_idx + "mul("sv.size();
        if (!doing) {
            continue;
        }

        if (idx >= line.size()) break;

        int consumed = 0;
        int a = 0;
        while (idx < line.size() && isdigit(line[idx])) {
            ++consumed;
            a *= 10;
            a += line[idx] - '0';
            ++idx;
        }
        if (consumed > 3 || consumed == 0) continue;
        if (idx >= line.size()) continue;

        if (line[idx] != ',') continue;
        ++idx;

        consumed = 0;
        int b = 0;
        while (idx < line.size() && isdigit(line[idx])) {
            ++consumed;
            b *= 10;
            b += line[idx] - '0';
            ++idx;
        }
        if (idx >= line.size()) continue;

        if (line[idx] != ')') continue;
        out.emplace_back(a, b);
    }
    return out;
}

int part2(string line) {
    auto input = parse_input2(line);

    auto stuff =
        input | views::transform([](auto p) { return p.first * p.second; });

    return ranges::fold_left(stuff, 0, plus<int>{});

    return 0;
}

int main() {
    ifstream file("inputs/day3.txt");

    string line;
    vector<string> lines;
    string full_input;
    while (std::getline(file, line)) {
        lines.push_back(line);
        full_input += line;
    }

    cout << "part1: " << part1(full_input) << '\n';
    cout << "part2: " << part2(full_input) << '\n';
}
