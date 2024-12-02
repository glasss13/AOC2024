#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

vector<vector<int>> parse_input(vector<string> const& lines) {
    return grid(lines);
}

int part1(vector<string> lines) {
    auto input = parse_input(lines);

    return ranges::count_if(input, [](const auto& line) {
        auto pairs = line | views::slide(2);

        auto diffs =
            pairs | views::transform([](auto x) { return x[0] - x[1]; });

        bool asc = ranges::all_of(diffs, [](auto diff) { return diff < 0; }) ||
                   ranges::all_of(diffs, [](auto diff) { return diff > 0; });

        bool ranged = ranges::all_of(
            diffs, [](auto diff) { return abs(diff) > 0 && abs(diff) <= 3; });
        return asc && ranged;
    });
}

int part2(vector<string> lines) {
    auto input = parse_input(lines);

    auto is_good = [](const auto& line) {
        auto pairs = line | views::slide(2);

        auto diffs =
            pairs | views::transform([](auto x) { return x[0] - x[1]; });

        bool asc = ranges::all_of(diffs, [](auto diff) { return diff < 0; }) ||
                   ranges::all_of(diffs, [](auto diff) { return diff > 0; });

        bool ranged = ranges::all_of(
            diffs, [](auto diff) { return abs(diff) > 0 && abs(diff) <= 3; });
        return asc && ranged;
    };

    return ranges::count_if(input, [&is_good](const auto& line) {
        for (size_t i = 0; i < line.size(); ++i) {
            auto cpy = line;
            cpy.erase(cpy.begin() + i);

            if (is_good(cpy)) {
                return true;
            }
        }

        return false;
    });
}

int main() {
    ifstream file("inputs/day2.txt");

    string line;
    vector<string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    cout << "part1: " << part1(lines) << '\n';
    cout << "part2: " << part2(lines) << '\n';
}
