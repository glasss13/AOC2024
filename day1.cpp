#include <bits/stdc++.h>

using namespace std;

pair<vector<int>, vector<int>> parse_input(vector<string> const& lines) {
    vector<int> col1;
    vector<int> col2;

    for (auto const& line : lines) {
        stringstream ss(line);

        int a_num, b_num;
        ss >> a_num >> b_num;

        col1.push_back(a_num);
        col2.push_back(b_num);
    }

    return {col1, col2};
}

int part1(vector<string> lines) {
    auto [col1, col2] = parse_input(lines);

    ranges::sort(col1);
    ranges::sort(col2);

    int ret = 0;
    for (int i = 0; i < col1.size(); i++) {
        ret += abs(col1[i] - col2[i]);
    }
    return ret;
}

int part2(vector<string> lines) {
    auto [col1, col2] = parse_input(lines);
    unordered_set included(col1.begin(), col1.end());

    int ret = 0;
    for (int num : col2) {
        if (included.contains(num)) {
            ret += num;
        }
    }

    return ret;
}

int main() {
    ifstream file("inputs/day1.txt");

    string line;
    vector<string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    cout << "part1: " << part1(lines) << '\n';
    cout << "part2: " << part2(lines) << '\n';
}
