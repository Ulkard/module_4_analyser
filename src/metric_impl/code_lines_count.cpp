#include "metric_impl/code_lines_count.hpp"

#include <algorithm>
#include <print>
#include <string>
#include <string_view>
#include <unistd.h>
#include <variant>
#include <ranges>


#include "utils.hpp"

using namespace std::string_view_literals;

namespace analyser::metric::metric_impl {

std::pair<int, int> extractLineNumbers(const std::string_view line) {
  size_t bracket = line.find('[');
  size_t comma = line.find(",", bracket);
  int start = ToInt(line.substr(bracket + 1, comma - bracket - 1));

  bracket = line.find('[', comma);
  comma = line.find(",", bracket);
  int end = ToInt(line.substr(bracket + 1, comma - bracket - 1));

  return { start, end };
}

inline int getDiff(const std::pair<int, int> scope) {
  return scope.second - scope.first + 1;
}

int extractCommentLineCount(const std::string_view ast) {
  auto lines = ast | std::views::split('\n');
  return std::ranges::fold_left(lines, 0, [](int, auto line) {
    return std::ranges::contains_subrange(line, "comment"sv)
               ? 0
               : getDiff(extractLineNumbers(std::string_view(line)));
  });
}

int countEmptyLines(std::string_view ast) {
    auto empty_lines_count = ast | std::views::split('\n') | std::views::drop(1) 
    | std::views::adjacent_transform<2>([](auto &&lhs, auto &&rhs) {
        auto left = extractLineNumbers(std::string_view(lhs));
        auto right = extractLineNumbers(std::string_view(rhs));
        return std::max(right.first - left.second - 1, 0);
    });

    return std::ranges::fold_left(empty_lines_count, 0, std::plus<int>());
}


MetricResult::ValueType
CodeLinesCountMetric::CalculateImpl(const function::Function &f) const {
  size_t f_body_pos = f.ast.find("body");
  int body_size = getDiff(extractLineNumbers(f.ast.substr(f_body_pos)));
  int comments = extractCommentLineCount(f.ast.substr(f_body_pos));
  int empty_lines = countEmptyLines(f.ast.substr(f_body_pos));

  return body_size - comments - empty_lines;
}

std::string CodeLinesCountMetric::Name() const { return "CodeLinesCount"; }

} // namespace analyser::metric::metric_impl
