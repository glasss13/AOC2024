#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

pair<ll, ll> parse_line(string_view l, char delim = '+') {
    auto p1 = l.find(delim) + 1;
    auto p2 = l.rfind(delim) + 1;

    ll a, b;
    from_chars(l.begin() + p1, l.end(), a);
    from_chars(l.begin() + p2, l.end(), b);

    return {a, b};
}

ll part1(vector<string> lines) {
    auto chunks = lines | views::chunk(4);

    auto tokens = chunks | views::transform([](auto chunk) {
                      string a_line = chunk[0];
                      string b_line = chunk[1];
                      string prize_line = chunk[2];

                      auto [x_1, y_1] = parse_line(a_line);
                      auto [x_2, y_2] = parse_line(b_line);
                      auto [x, y] = parse_line(prize_line, '=');

                      ll b = (y * x_1 - y_1 * x) / (x_1 * y_2 - y_1 * x_2);

                      ll a = (x - b * x_2) / x_1;

                      if (a * x_1 + b * x_2 == x && a * y_1 + b * y_2 == y &&
                          a >= 0 && b >= 0) {
                          return a * 3 + b;
                      } else {
                          return 0ll;
                      }
                  });

    return ranges::fold_left(tokens, 0ll, plus<ll>{});
}

ll part2(vector<string> lines) {
    ll res = 0;
    for (int i = 0; i < lines.size(); i += 4) {
        string a_line = lines[i];
        string b_line = lines[i + 1];
        string prize_line = lines[i + 2];

        auto [x_1, y_1] = parse_line(a_line);
        auto [x_2, y_2] = parse_line(b_line);
        auto [x, y] = parse_line(prize_line, '=');

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
