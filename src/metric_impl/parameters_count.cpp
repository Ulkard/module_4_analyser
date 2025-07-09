#include "metric_impl/parameters_count.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "utils.hpp"

namespace analyser::metric::metric_impl {

std::pair<int, int> extractEndPos(const std::string_view line) {
  size_t bracket = line.rfind('[');
  size_t comma = line.find(",", bracket);
  int line_num = ToInt(line.substr(bracket + 1, comma - bracket - 1));

  bracket = line.find(']', comma);
  int column_num = ToInt(line.substr(comma + 2, bracket - comma - 2));
  return { line_num, column_num };
}

size_t getIndent(const std::string_view line) {
    return line.find_first_not_of(' ');
}

MetricResult::ValueType CountParametersMetric::CalculateImpl(const function::Function& f) const {
    size_t params_begin = f.ast.find("parameters");
    size_t param_indent = params_begin - f.ast.rfind('\n', params_begin)-1;
    const auto params = f.ast.substr(params_begin);
    auto parameters_block_end = extractEndPos(params.substr(0, params.find('\n')));
    auto param_lines =
        f.ast.substr(params_begin) | std::views::split('\n') |
        std::views::drop(1) |
        std::views::take_while([parameters_block_end](auto &&line) {
            auto line_end = extractEndPos(std::string_view(line));
            return line_end.first < parameters_block_end.first ||
                 ((line_end.first == parameters_block_end.first) &&
                  line_end.second <= parameters_block_end.second);
        });
        
    return std::ranges::count_if(param_lines, [param_indent](const auto& line){ 
        constexpr size_t indent_step = 2;
        return getIndent(std::string_view(line)) == param_indent + indent_step; });
}

std::string CountParametersMetric::Name() const {
    return "CountParametersMetric";
}

}  // namespace analyser::metric::metric_impl
