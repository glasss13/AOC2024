#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

struct Robot {
    int x, y;
    int dx, dy;
};

Robot parse_line(string_view l) {
    auto e1 = l.find('=') + 1;
    auto e2 = l.rfind('=') + 1;
    auto c1 = l.find(',') + 1;
    auto c2 = l.rfind(',') + 1;

    int x, y, dx, dy;
    from_chars(l.begin() + e1, l.end(), x);
    from_chars(l.begin() + c1, l.end(), y);
    from_chars(l.begin() + e2, l.end(), dx);
    from_chars(l.begin() + c2, l.end(), dy);

    return Robot{x, y, dx, dy};
}

ll part1(vector<string> lines) {
    vector<Robot> robots;
    for (const auto& line : lines) {
        robots.push_back(parse_line(line));
    }

    int w = 101;
    int h = 103;

    for (int second = 0; second < 100; ++second) {
        for (auto& robot : robots) {
            robot.x = (robot.x + robot.dx + w) % w;
            robot.y = (robot.y + robot.dy + h) % h;
        }
    }

    int qw = w / 2;
    int qh = h / 2;

    int tl{}, tr{}, bl{}, br{};
    for (const auto& robot : robots) {
        if (robot.x - qw < 0) {
            if (robot.y - qh < 0) {
                ++tl;
            } else if (robot.y - qh > 0) {
                ++bl;
            }
        } else if (robot.x - qw > 0) {
            if (robot.y - qh < 0) {
                ++tr;
            } else if (robot.y - qh > 0) {
                ++br;
            }
        }
    }

    return tl * tr * bl * br;
}

ll part2(vector<string> lines) {
    vector<Robot> robots;
    for (const auto& line : lines) {
        robots.push_back(parse_line(line));
    }

    int w = 101;
    int h = 103;

    int second = 0;
    while (true) {
        int x_sum{}, y_sum{};
        for (auto& robot : robots) {
            x_sum += robot.x;
            y_sum += robot.y;
        }
        double x_mean = static_cast<double>(x_sum) / robots.size();
        double y_mean = static_cast<double>(y_sum) / robots.size();

        double x_resid{}, y_resid{};
        for (auto& robot : robots) {
            x_resid += (robot.x - x_mean) * (robot.x - x_mean);
            y_resid += (robot.y - y_mean) * (robot.y - y_mean);
        }

        double x_var = x_resid / (robots.size() - 1);
        double y_var = y_resid / (robots.size() - 1);

        if (x_var < 350 && y_var < 420) {
            vector<string> s(h, string(w, '.'));

            for (auto& robot : robots) {
                s[robot.y][robot.x] = '#';
            }
            for (const auto& l : s) {
                cout << l << '\n';
            }
            return second;
        }

        for (auto& robot : robots) {
            robot.x = (robot.x + robot.dx + w) % w;
            robot.y = (robot.y + robot.dy + h) % h;
        }

        ++second;
    }

    return -1;
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day14.txt") : ifstream("sample.txt");

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
