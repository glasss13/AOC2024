#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

pair<ll, ll> area_perim(vector<string> const& g, int i, int j, char id,
                        set<pair<int, int>>& seen) {
    int r = g.size();
    int c = g[0].size();

    if (i < 0 || i >= r || j < 0 || j >= c || g[i][j] != id) {
        return {0, 1};
    }

    auto p = make_pair(i, j);
    if (seen.contains(p)) {
        return {0, 0};
    }
    seen.emplace(i, j);

    pair<ll, ll> ret = {1, 0};
    for (auto [di, dj] : DIRS) {
        auto [a, b] = area_perim(g, i + di, j + dj, id, seen);
        ret.first += a;
        ret.second += b;
    }
    return ret;
}

ll part1(vector<string> lines) {
    set<pair<int, int>> seen;

    int r = lines.size();
    int c = lines[0].size();

    ll ret = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (seen.contains({i, j})) continue;

            auto [a, b] = area_perim(lines, i, j, lines[i][j], seen);
            ret += a * b;
        }
    }

    return ret;
}

ll region_area(vector<string> const& g, int i, int j, char id,
               set<pair<int, int>>& seen, set<pair<int, int>>& in_region) {
    int r = g.size();
    int c = g[0].size();

    if (i < 0 || i >= r || j < 0 || j >= c || g[i][j] != id) {
        return 0;
    }
    in_region.emplace(i, j);

    auto p = make_pair(i, j);
    if (seen.contains(p)) {
        return 0;
    }
    seen.emplace(i, j);

    ll ret = 1;
    for (auto [di, dj] : DIRS) {
        ret += region_area(g, i + di, j + dj, id, seen, in_region);
    }
    return ret;
}

ll part2(vector<string> lines) {
    set<pair<int, int>> seen;

    int r = lines.size();
    int c = lines[0].size();

    ll ret = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (seen.contains({i, j})) continue;

            set<pair<int, int>> in_region;

            auto area = region_area(lines, i, j, lines[i][j], seen, in_region);

            ll sides = 0;

            for (auto [k, l] : in_region) {
                bool has_up = in_region.contains({k - 1, l});
                bool has_down = in_region.contains({k + 1, l});
                bool has_right = in_region.contains({k, l + 1});
                bool has_left = in_region.contains({k, l - 1});

                bool has_tr = in_region.contains({k - 1, l + 1});
                bool has_tl = in_region.contains({k - 1, l - 1});
                bool has_br = in_region.contains({k + 1, l + 1});
                bool has_bl = in_region.contains({k + 1, l - 1});

                sides += !has_up && !has_right;
                sides += !has_up && !has_left;
                sides += !has_down && !has_right;
                sides += !has_down && !has_left;
                sides += has_up && has_right && !has_tr;
                sides += has_up && has_left && !has_tl;
                sides += has_down && has_right && !has_br;
                sides += has_down && has_left && !has_bl;
            }

            ret += area * sides;
        }
    }

    return ret;
}

int main() {
    ifstream file("inputs/day12.txt");
    // ifstream file("in.txt");

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
