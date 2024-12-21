#include <bits/stdc++.h>

#include "utils.hpp"

using namespace std;

string part1(vector<string> lines) {
    auto space_idx = lines[0].find(": ");

    ll reg_a = stoll(lines[0].substr(space_idx + 2));
    ll reg_b = 0;
    ll reg_c = 0;

    space_idx = lines[4].find(' ');

    string instructions_str = lines[4].substr(space_idx + 1);

    stringstream ss(instructions_str);
    string cur;
    vector<ll> instructions;
    while (getline(ss, cur, ',')) {
        instructions.push_back(stoll(cur));
    }

    ll program_counter = 0;

    auto get_combo = [&](ll x) {
        if (x >= 0 && x <= 3) {
            return x;
        }

        if (x == 4) return reg_a;
        if (x == 5) return reg_b;
        if (x == 6) return reg_c;
        return -1ll;
    };

    vector<ll> out;

    while (program_counter < instructions.size()) {
        ll opcode = instructions[program_counter];
        ll operand = instructions[program_counter + 1];

        if (opcode == 0) {
            reg_a = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else if (opcode == 1) {
            reg_b = reg_b ^ operand;
            program_counter += 2;
        } else if (opcode == 2) {
            reg_b = 7 & get_combo(operand);
            program_counter += 2;
        } else if (opcode == 3) {
            if (reg_a == 0) {
                program_counter += 2;
            } else {
                program_counter = operand;
            }
        } else if (opcode == 4) {
            reg_b = reg_b ^ reg_c;
            program_counter += 2;
        } else if (opcode == 5) {
            out.push_back(get_combo(operand) & 7);
            program_counter += 2;
        } else if (opcode == 6) {
            reg_b = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else if (opcode == 7) {
            reg_c = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else {
            cout << "ERORR\n";
        }
    }

    string out_str;
    for (auto x : out) {
        out_str += to_string(x);
        out_str += ',';
    }

    return out_str.substr(0, out_str.size() - 1);
}

ll validate(const vector<ll>& instructions, ll reg_a) {
    ll reg_b = 0;
    ll reg_c = 0;

    ll program_counter = 0;

    auto get_combo = [&](ll x) {
        if (x >= 0 && x <= 3) {
            return x;
        }

        if (x == 4) return reg_a;
        if (x == 5) return reg_b;
        if (x == 6) return reg_c;
        return -1ll;
    };

    ll out_idx = 0;
    ll similarity = 0;

    while (program_counter < instructions.size()) {
        ll opcode = instructions[program_counter];
        ll operand = instructions[program_counter + 1];

        if (opcode == 0) {
            reg_a = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else if (opcode == 1) {
            reg_b = reg_b ^ operand;
            program_counter += 2;
        } else if (opcode == 2) {
            reg_b = 7 & get_combo(operand);
            program_counter += 2;
        } else if (opcode == 3) {
            if (reg_a == 0) {
                program_counter += 2;
            } else {
                program_counter = operand;
            }
        } else if (opcode == 4) {
            reg_b = reg_b ^ reg_c;
            program_counter += 2;
        } else if (opcode == 5) {
            if (instructions[out_idx] == (get_combo(operand) & 7)) {
                ++similarity;
            }
            ++out_idx;
            program_counter += 2;
        } else if (opcode == 6) {
            reg_b = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else if (opcode == 7) {
            reg_c = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else {
            cout << "ERORR\n";
        }
    }

    return similarity;
}

vector<ll> compute(const vector<ll>& instructions, ll reg_a) {
    ll reg_b = 0;
    ll reg_c = 0;

    ll program_counter = 0;

    auto get_combo = [&](ll x) {
        if (x >= 0 && x <= 3) {
            return x;
        }

        if (x == 4) return reg_a;
        if (x == 5) return reg_b;
        if (x == 6) return reg_c;
        return -1ll;
    };

    ll out_idx = 0;
    vector<ll> out;

    while (program_counter < instructions.size()) {
        ll opcode = instructions[program_counter];
        ll operand = instructions[program_counter + 1];

        if (opcode == 0) {
            reg_a = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else if (opcode == 1) {
            reg_b = reg_b ^ operand;
            program_counter += 2;
        } else if (opcode == 2) {
            reg_b = 7 & get_combo(operand);
            program_counter += 2;
        } else if (opcode == 3) {
            if (reg_a == 0) {
                program_counter += 2;
            } else {
                program_counter = operand;
            }
        } else if (opcode == 4) {
            reg_b = reg_b ^ reg_c;
            program_counter += 2;
        } else if (opcode == 5) {
            out.push_back(get_combo(operand) & 7);
            ++out_idx;
            program_counter += 2;
        } else if (opcode == 6) {
            reg_b = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else if (opcode == 7) {
            reg_c = reg_a / pow(2, get_combo(operand));
            program_counter += 2;
        } else {
            cout << "ERORR\n";
        }
    }

    return out;
}

ll part2(vector<string> lines) {
    auto space_idx = lines[4].find(' ');

    string instructions_str = lines[4].substr(space_idx + 1);

    stringstream ss(instructions_str);
    string cur;
    vector<ll> instructions;
    while (getline(ss, cur, ',')) {
        instructions.push_back(stoll(cur));
    }

    ll reg_a = 35184731236906ll;
    reg_a = 202991746427434ll;

    while (true) {
        auto x = compute(instructions, reg_a);
        for (auto y : x) {
            cout << y << ' ';
        }

        cout << '\n';
        cout << reg_a << '\n';
        ll inp;
        cin >> inp;
        reg_a += inp;
    }

    return reg_a;
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day17.txt") : ifstream("sample.txt");

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
