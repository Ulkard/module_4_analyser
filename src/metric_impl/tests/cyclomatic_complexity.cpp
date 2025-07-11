#include "metric_impl/cyclomatic_complexity.hpp"
#include "test_helpers.h"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(CyclomaticComplexity, simple) {
    int result = getMetric<CyclomaticComplexityMetric>("simple.py");
    EXPECT_EQ(result, 2);
}

TEST(CyclomaticComplexity, exceptions) {
    int result = getMetric<CyclomaticComplexityMetric>("exceptions.py");
    EXPECT_EQ(result, 3);
}

TEST(CyclomaticComplexity, if) {
    int result = getMetric<CyclomaticComplexityMetric>("if.py");
    EXPECT_EQ(result, 2);
}

TEST(CyclomaticComplexity, loops) {
    int result = getMetric<CyclomaticComplexityMetric>("loops.py");
    EXPECT_EQ(result, 4);
}

TEST(CyclomaticComplexity, match_case) {
    int result = getMetric<CyclomaticComplexityMetric>("match_case.py");
    EXPECT_EQ(result, 2);
}

TEST(CyclomaticComplexity, nested_if) {
    int result = getMetric<CyclomaticComplexityMetric>("nested_if.py");
    EXPECT_EQ(result, 4);
}

TEST(CyclomaticComplexity, ternary) {
    int result = getMetric<CyclomaticComplexityMetric>("ternary.py");
    EXPECT_EQ(result, 3);
}

}  // namespace analyser::metric::metric_impl
