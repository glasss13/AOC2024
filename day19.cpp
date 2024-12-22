#include <bits/stdc++.h>

#include <sstream>

#include "utils.hpp"

using namespace std;

ll n_ways(const string& line, const vector<string>& allowed) {
    int n = line.size();
    vector<ll> dp(n + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (const auto& str : allowed) {
            if (str.size() > i) continue;

            bool good = true;
            for (int j = 0; j < str.size(); ++j) {
                if (line[i - str.size() + j] != str[j]) good = false;
            }

            if (good) {
                dp[i] += dp[i - str.size()];
            }
        }
    }

    return dp.back();
}

ll part1(vector<string> lines) {
    stringstream ss(" " + lines[0]);
    string cur;

    vector<string> comps;

    while (getline(ss, cur, ',')) {
        cur.erase(0, 1);  // remove whitespace
        comps.push_back(cur);
    }

    ll res = 0;
    for (int i = 2; i < lines.size(); ++i) {
        res += n_ways(lines[i], comps) > 0;
    }

    return res;
}

ll part2(vector<string> lines) {
    stringstream ss(" " + lines[0]);
    string cur;

    vector<string> comps;

    while (getline(ss, cur, ',')) {
        cur.erase(0, 1);  // remove whitespace
        comps.push_back(cur);
    }

    ll res = 0;
    for (int i = 2; i < lines.size(); ++i) {
        res += n_ways(lines[i], comps);
    }

    return res;
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day19.txt") : ifstream("sample.txt");

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
