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
    auto take_collect = [](auto range) {
        return range |
               views::take_while([](const string& x) { return !x.empty(); }) |
               ranges::to<vector<string>>();
    };

    return {take_collect(lines | views::all),
            take_collect(lines | views::reverse)};
}

vector<int> parse_comma_delim(const string& str) {
    return str | views::split(',') |
           views::transform([](auto x) { return stoi(string_view(x)); }) |
           ranges::to<vector<int>>();
}

int part1(vector<string> lines) {
    auto [ordering_in, updates_in] = parse_components(lines);

    auto updates = updates_in | views::transform([](const string& update) {
                       return parse_comma_delim(update);
                   });

    auto ordering = parse_ordering(ordering_in);

    auto is_valid_update = [&](const vector<int>& update) {
        unordered_set<int> seen;

        for (int n : update) {
            if (seen.contains(n)) {
                return false;
            }

            seen.insert(ordering[n].begin(), ordering[n].end());
        }
        return true;
    };

    auto valid_updates = updates | views::filter(is_valid_update);

    auto valid_medians =
        valid_updates | views::transform([](const vector<int>& update) {
            return update[update.size() / 2];
        });

    return ranges::fold_left(valid_medians, 0, plus{});
}

int part2(vector<string> lines) {
    auto [ordering_in, updates_in] = parse_components(lines);

    auto updates = updates_in | views::transform([](const string& update) {
                       return parse_comma_delim(update);
                   });

    auto ordering = parse_ordering(ordering_in);

    auto is_valid_update = [&](const vector<int>& update) {
        unordered_set<int> seen;

        for (int n : update) {
            if (seen.contains(n)) {
                return false;
            }

            seen.insert(ordering[n].begin(), ordering[n].end());
        }
        return true;
    };

    auto invalid_updates = updates | views::filter([&](const auto& x) {
                               return !is_valid_update(x);
                           });

    auto sorted_updates = invalid_updates | views::transform([&](auto update) {
                              ranges::sort(update, [&](int a, int b) {
                                  return ordering[a].contains(b);
                              });
                              return update;
                          });

    auto medians = sorted_updates | views::transform([](const auto& u) {
                       return u[u.size() / 2];
                   });

    return ranges::fold_left(medians, 0, plus{});
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
