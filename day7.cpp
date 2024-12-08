#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

vector<pair<long long, vector<long long>>> parse_input(vector<string> lines) {
    vector<pair<long long, vector<long long>>> out;
    for (const auto& line : lines) {
        int idx = line.find(':');
        long long target = stoll(line.substr(0, idx));
        auto vals = nums<ll>(line.substr(idx + 1));
        out.emplace_back(target, vals);
    }
    return out;
}

bool sum_reachable(const vector<ll>& nums, ll target, ll cur_sum, int idx,
                   bool cat = true) {
    if (cur_sum > target) return false;
    if (idx == nums.size() && cur_sum == target) {
        return true;
    }
    if (idx >= nums.size()) {
        return false;
    }
    bool res = sum_reachable(nums, target, cur_sum + nums[idx], idx + 1, cat) ||
               sum_reachable(nums, target, cur_sum * nums[idx], idx + 1, cat);

    if (cat) {
        res = res ||
              sum_reachable(nums, target,
                            stol(to_string(cur_sum) + to_string(nums[idx])),
                            idx + 1, cat);
    }
    return res;
}

ll part1(vector<string> lines) {
    auto inp = parse_input(lines);

    ll res = 0;
    for (auto t : inp) {
        if (sum_reachable(t.second, t.first, 0, 0, false)) {
            res += t.first;
        }
    }

    return res;
}

ll part2(vector<string> lines) {
    auto inp = parse_input(lines);

    ll res = 0;
    for (auto t : inp) {
        if (sum_reachable(t.second, t.first, 0, 0)) {
            res += t.first;
        }
    }

    return res;
}

int main() {
    ifstream file("inputs/day7.txt");

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
