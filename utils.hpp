#pragma once

#include <bits/stdc++.h>

using ll = long long;

template <typename T = int>
constexpr std::vector<T> nums(const std::string& line) {
    std::stringstream stream(line);
    return std::views::istream<T>(stream) | std::ranges::to<std::vector<T>>();
}

constexpr std::vector<std::vector<int>> grid(
    const std::vector<std::string>& lines) {
    return std::views::transform(lines, nums<int>) |
           std::ranges::to<std::vector<std::vector<int>>>();
}

constexpr std::array<std::pair<int, int>, 8> DIRS8 = {
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};

constexpr std::array<std::pair<int, int>, 4> DIRS{
    {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

// idk why the standard doesn't have this lol
int stoi(std::string_view x) {
    int ret = 0;
    for (auto c : x) {
        ret *= 10;
        ret += c - '0';
    }
    return ret;
}
