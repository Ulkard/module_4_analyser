#pragma once

#include <charconv>
#include <cstddef>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>

inline int ToInt(std::string_view value) {
    int result{};
    auto [parse_end_ptr, error_code] = std::from_chars(value.begin(), value.end(), result);
    if (error_code != std::errc{} || parse_end_ptr != value.data() + value.size()) {
        throw std::invalid_argument("Cannot convert '" + std::string(value) + "' to integral");
    }
    return result;
}

inline std::string_view extractKeyword(const std::string_view line) {
    size_t start = line.find('(') + 1;
    size_t end = line.find(' ', start);
    return line.substr(start, end - start);
}
