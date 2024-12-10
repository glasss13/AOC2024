#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

struct Block {
    int id;
    int length;
    bool free_space;
};

vector<Block> parse_input(string line) {
    vector<Block> out;

    for (int i = 0; i < line.size(); ++i) {
        if (i % 2 == 0) {
            out.emplace_back(i / 2, line[i] - '0', false);
        } else {
            out.emplace_back(0, line[i] - '0', true);
        }
    }

    return out;
}

ll part1(vector<string> lines) {
    auto inp = parse_input(lines[0]);

    ll res = 0;
    int real_pos = 0;

    int l = 0;
    int r = inp.size() - 1;

    while (l <= r) {
        auto& block = inp[l];
        if (!block.free_space) {
            for (int i = 0; i < block.length; ++i) {
                res += (real_pos + i) * block.id;
            }
            real_pos += block.length;
            ++l;
        } else {
            if (block.length == 0) {
                ++l;
                continue;
            }

            while (l <= r && (inp[r].free_space || inp[r].length == 0)) {
                --r;
            }

            if (l > r) {
                break;
            }

            res += real_pos * inp[r].id;
            --inp[r].length;
            --block.length;
            ++real_pos;
        }
    }

    return res;
}

ll part2(vector<string> lines) {
    auto inp = parse_input(lines[0]);

    int l = 0;
    int r = inp.size() - 1;

    for (int i = inp.size() - 1; i >= 0; --i) {
        auto block = inp[i];
        if (block.free_space) continue;

        auto slot = ranges::find_if(inp, [&](const Block& b) {
            return b.free_space && b.length >= block.length;
        });

        if (slot > inp.begin() + i) continue;

        slot->length -= block.length;
        inp[i].free_space = true;
        inp[i].id = 0;
        inp.insert(slot, block);
    }

    ll res = 0;
    int real_pos = 0;
    for (auto block : inp) {
        for (int i = 0; i < block.length; ++i) {
            res += (real_pos + i) * block.id;
        }
        real_pos += block.length;
    }
    return res;
}

int main() {
    ifstream file("inputs/day9.txt");

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
