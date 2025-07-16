#include "metric_impl/cyclomatic_complexity.hpp"

#include <print>
#include <string_view>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

#include "utils.hpp"


namespace analyser::metric::metric_impl {

const std::unordered_set<std::string_view> keywords{ 
    "if_statement", "alternative", 
    "while_statement", "for_statement",
    "try_statement", "match_statement", 
    "assert_statement", "conditional_expression"};

MetricResult::ValueType CyclomaticComplexityMetric::CalculateImpl(const function::Function& f) const {
    auto keyword_lines =
        substrByKeyword(f.ast, "body") | std::views::split('\n') |
        std::views::transform([](auto &&line) {
          return extractKeyword(std::string_view(line));
        });

    return std::ranges::count_if(keyword_lines, [](const auto& line){ 
        return keywords.contains(line);
    }) + 1;
}

std::string CyclomaticComplexityMetric::Name() const {
    return "CyclomaticComplexity";
}

}  // namespace analyser::metric::metric_impl
