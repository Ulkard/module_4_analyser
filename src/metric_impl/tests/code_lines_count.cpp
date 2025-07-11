#include "metric_impl/code_lines_count.hpp"
#include "test_helpers.h"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(CodeLinesCount, simple) {
    int result = getMetric<CodeLinesCountMetric>("simple.py");
    EXPECT_EQ(result, 5);
}

TEST(CodeLinesCount, comments) {
    int result = getMetric<CodeLinesCountMetric>("comments.py");
    EXPECT_EQ(result, 3);
}

TEST(CodeLinesCount, many_lines) {
    int result = getMetric<CodeLinesCountMetric>("many_lines.py");
    EXPECT_EQ(result, 11);
}

}  // namespace analyser::metric::metric_impl
