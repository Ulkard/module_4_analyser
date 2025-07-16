#include "metric_impl/code_lines_count.hpp"

#include <algorithm>
#include <cstddef>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <unistd.h>
#include <unordered_set>
#include <variant>

#include "utils.hpp"

using namespace std::string_view_literals;
namespace rv = std::ranges::views;

namespace analyser::metric::metric_impl {

std::pair<int, int> extractLineNumbers(const std::string_view line) {
    size_t bracket = line.find('[');
    size_t comma = line.find(",", bracket);
    int start = ToInt(line.substr(bracket + 1, comma - bracket - 1));

    bracket = line.find('[', comma);
    comma = line.find(",", bracket);
    int end = ToInt(line.substr(bracket + 1, comma - bracket - 1));

    return {start, end};
}

inline int getDiff(const std::pair<int, int> scope) { return scope.second - scope.first + 1; }

int extractCommentLineCount(const std::string_view ast) {
    // std::println("{}", ast);
    auto lines = ast | rv::split('\n');
    return std::ranges::fold_left(lines, 0, [](int init, auto line) {
        return init + (std::ranges::contains_subrange(line, "comment"sv)
                           ? getDiff(extractLineNumbers(std::string_view(line)))
                           : 0);
    });
}

int countEmptyLines(std::string_view ast) {
    std::unordered_set<size_t> filled_lines;
    size_t lines_total = getDiff(extractLineNumbers(ast));
    auto lines = ast | rv::split('\n') | rv::drop(1);

    std::ranges::for_each(lines, ([&filled_lines](auto &&line) {
                              auto line_nums = extractLineNumbers(std::string_view(line));
                              filled_lines.insert(line_nums.first);
                              filled_lines.insert(line_nums.second);
                          }));

    return lines_total - filled_lines.size();  // std::ranges::fold_left(empty_lines_count, 0, std::plus<int>());
}


MetricResult::ValueType
CodeLinesCountMetric::CalculateImpl(const function::Function &f) const {
    const std::string_view body_sv = substrByKeyword(f.ast, "body");
    
    int body_size = getDiff(extractLineNumbers(body_sv));
    int comments = extractCommentLineCount(body_sv);
    int empty_lines = countEmptyLines(body_sv);
    return body_size - comments - empty_lines;
}

std::string CodeLinesCountMetric::Name() const { return "CodeLinesCount"; }

}  // namespace analyser::metric::metric_impl
