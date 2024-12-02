#pragma once

#include <bits/stdc++.h>

std::vector<int> nums(const std::string& line) {
    auto stream = std::istringstream(line);
    return std::views::istream<int>(stream) |
           std::ranges::to<std::vector<int>>();
}

std::vector<std::vector<int>> grid(const std::vector<std::string>& lines) {
    return std::views::transform(lines, nums) |
           std::ranges::to<std::vector<std::vector<int>>>();
}
