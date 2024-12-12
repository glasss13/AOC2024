#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

ll evolve_number(ll x, int steps, vector<unordered_map<ll, ll>>& dp) {
    if (steps == 0) {
        return 1;
    }

    if (dp[steps - 1].contains(x)) {
        return dp[steps - 1][x];
    }

    ll ret;
    if (x == 0) {
        ret = evolve_number(1, steps - 1, dp);
    } else if (int digits = static_cast<int>(log10(x)) + 1; digits % 2 == 0) {
        auto div = static_cast<ll>(pow(10, digits / 2));
        auto a = evolve_number(x % div, steps - 1, dp);
        auto b = evolve_number(x / div, steps - 1, dp);
        ret = a + b;
    } else {
        ret = evolve_number(x * 2024, steps - 1, dp);
    }

    dp[steps - 1][x] = ret;

    return ret;
}

ll part1(vector<string> lines) {
    string line = lines[0];

    vector<ll> inp = nums<ll>(line);
    ll ret = 0;

    vector<unordered_map<ll, ll>> dp(25);

    for (auto x : inp) {
        ret += evolve_number(x, 25, dp);
    }

    return ret;
}

ll part2(vector<string> lines) {
    string line = lines[0];

    vector<ll> inp = nums<ll>(line);
    ll ret = 0;

    vector<unordered_map<ll, ll>> dp(75);
    for (auto x : inp) {
        ret += evolve_number(x, 75, dp);
    }

    return ret;
}

int main() {
    ifstream file("inputs/day11.txt");

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
