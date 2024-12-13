#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

pair<ll, ll> parse_line(string const& line) {
    auto plus_pos = line.find('+');
    auto comma_pos = line.find(',');
    auto a = stoll(line.substr(plus_pos + 1, comma_pos));

    plus_pos = line.find('+', comma_pos);
    auto b = stoll(line.substr(plus_pos + 1));

    return {a, b};
}

pair<ll, ll> parse_prize(string const& line) {
    auto equal_pos = line.find('=');
    auto comma_pos = line.find(',');

    auto x = stoll(line.substr(equal_pos + 1, comma_pos));
    equal_pos = line.find('=', comma_pos);
    auto y = stoll(line.substr(equal_pos + 1));

    return {x, y};
}

ll part1(vector<string> lines) {
    ll res = 0;
    for (int i = 0; i < lines.size(); i += 4) {
        string a_line = lines[i];
        string b_line = lines[i + 1];
        string prize_line = lines[i + 2];

        auto [x_1, y_1] = parse_line(a_line);
        auto [x_2, y_2] = parse_line(b_line);
        auto [x, y] = parse_prize(prize_line);

        ll b = (y * x_1 - y_1 * x) / (x_1 * y_2 - y_1 * x_2);

        ll a = (x - b * x_2) / x_1;

        if (a * x_1 + b * x_2 == x && a * y_1 + b * y_2 == y && a >= 0 &&
            b >= 0) {
            res += a * 3 + b;
        }
    }

    return res;
}

ll part2(vector<string> lines) {
    ll res = 0;
    for (int i = 0; i < lines.size(); i += 4) {
        string a_line = lines[i];
        string b_line = lines[i + 1];
        string prize_line = lines[i + 2];

        auto [x_1, y_1] = parse_line(a_line);
        auto [x_2, y_2] = parse_line(b_line);
        auto [x, y] = parse_prize(prize_line);

        x += 10000000000000;
        y += 10000000000000;

        ll b = (y * x_1 - y_1 * x) / (x_1 * y_2 - y_1 * x_2);

        ll a = (x - b * x_2) / x_1;

        if (a * x_1 + b * x_2 == x && a * y_1 + b * y_2 == y && a >= 0 &&
            b >= 0) {
            res += a * 3 + b;
        }
    }

    return res;
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day13.txt") : ifstream("sample.txt");

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
