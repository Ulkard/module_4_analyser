#include "metric_impl/code_lines_count.hpp"
#include "test_helpers.h"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(CodeLinesCount, comments) {
    int result = getMetric<CodeLinesCountMetric>("comments.py");
    EXPECT_EQ(result, 3);
}

TEST(CodeLinesCount, exceptions) {
    int result = getMetric<CodeLinesCountMetric>("exceptions.py");
    EXPECT_EQ(result, 7);
}

TEST(CodeLinesCount, if) {
    int result = getMetric<CodeLinesCountMetric>("if.py");
    EXPECT_EQ(result, 3);
}

TEST(CodeLinesCount, loops) {
    int result = getMetric<CodeLinesCountMetric>("loops.py");
    EXPECT_EQ(result, 6);
}

TEST(CodeLinesCount, many_lines) {
    int result = getMetric<CodeLinesCountMetric>("many_lines.py");
    EXPECT_EQ(result, 11);
}

TEST(CodeLinesCount, many_parameters) {
    int result = getMetric<CodeLinesCountMetric>("many_parameters.py");
    EXPECT_EQ(result, 1);
}

TEST(CodeLinesCount, match_case) {
    int result = getMetric<CodeLinesCountMetric>("match_case.py");
    EXPECT_EQ(result, 7);
}

TEST(CodeLinesCount, nested_if) {
    int result = getMetric<CodeLinesCountMetric>("nested_if.py");
    EXPECT_EQ(result, 8);
}

TEST(CodeLinesCount, simple) {
    int result = getMetric<CodeLinesCountMetric>("simple.py");
    EXPECT_EQ(result, 5);
}

TEST(CodeLinesCount, ternary) {
    int result = getMetric<CodeLinesCountMetric>("ternary.py");
    EXPECT_EQ(result, 1);
}

}  // namespace analyser::metric::metric_impl
