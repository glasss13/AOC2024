#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

unordered_map<int, unordered_set<int>> parse_ordering(
    const vector<string>& lines) {
    unordered_map<int, unordered_set<int>> out;

    for (const auto& line : lines) {
        int bar_idx = line.find('|');

        int a = stoi(line.substr(0, bar_idx));
        int b = stoi(line.substr(bar_idx + 1));

        out[b].insert(a);
    }

    return out;
}

pair<vector<string>, vector<string>> parse_components(
    const vector<string>& lines) {
    vector<string> ordering;
    vector<string> updates;
    bool in_updates = false;

    for (const auto& line : lines) {
        if (line.empty()) {
            in_updates = true;
            continue;
        }

        if (in_updates) {
            updates.push_back(line);
        } else {
            ordering.push_back(line);
        }
    }

    return {ordering, updates};
}

vector<int> parse_comma_delim(const string& str) {
    vector<int> out;
    for (auto x : str | views::split(',')) {
        out.push_back(stoi(string_view(x)));
    }
    return out;
}

int part1(vector<string> lines) {
    auto [ordering_in, updates] = parse_components(lines);

    auto ordering = parse_ordering(ordering_in);

    int res = 0;

    for (const string& update : updates) {
        unordered_set<int> seen;
        vector<int> nums = parse_comma_delim(update);

        bool valid_line = true;
        for (int n : nums) {
            if (seen.contains(n)) {
                valid_line = false;
            }

            seen.insert(ordering[n].begin(), ordering[n].end());
        }

        if (!valid_line) continue;

        res += nums[nums.size() / 2];
    }

    return res;
}

int part2(vector<string> lines) {
    auto [ordering_in, updates] = parse_components(lines);

    auto ordering = parse_ordering(ordering_in);

    int res = 0;

    for (const string& update : updates) {
        unordered_set<int> seen;
        vector<int> nums = parse_comma_delim(update);

        bool valid_line = true;
        for (int n : nums) {
            if (seen.contains(n)) {
                valid_line = false;
            }

            seen.insert(ordering[n].begin(), ordering[n].end());
        }

        if (valid_line) continue;

        ranges::sort(nums,
                     [&](int a, int b) { return ordering[a].contains(b); });

        res += nums[nums.size() / 2];
    }

    return res;
}

int main() {
    ifstream file("inputs/day5.txt");

    string line;
    vector<string> lines;
    string full_input;
    while (std::getline(file, line)) {
        lines.push_back(line);
        full_input += line;
    }

    auto p1_start = chrono::high_resolution_clock::now();
    cout << "part1: " << part1(lines) << '\n';
    auto p2_start = chrono::high_resolution_clock::now();
    cout << "part2: " << part2(lines) << '\n';
    auto p2_end = chrono::high_resolution_clock::now();

    auto p1_time =
        chrono::duration_cast<chrono::microseconds>(p2_start - p1_start);
    auto p2_time =
        chrono::duration_cast<chrono::microseconds>(p2_end - p2_start);
    cout << "part1(µs): " << p1_time.count() << '\n';
    cout << "part2(µs): " << p2_time.count() << '\n';
}
