#include "metric_impl/parameters_count.hpp"
#include "test_helpers.h"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(ParametersCount, comments) {
    int result = getMetric<CountParametersMetric>("comments.py");
    EXPECT_EQ(result, 3);
}

TEST(ParametersCount, exceptions) {
    int result = getMetric<CountParametersMetric>("exceptions.py");
    EXPECT_EQ(result, 0);
}

TEST(ParametersCount, if) {
    int result = getMetric<CountParametersMetric>("if.py");
    EXPECT_EQ(result, 1);
}

TEST(ParametersCount, loops) {
    int result = getMetric<CountParametersMetric>("loops.py");
    EXPECT_EQ(result, 1);
}

TEST(ParametersCount, many_lines) {
    int result = getMetric<CountParametersMetric>("many_lines.py");
    EXPECT_EQ(result, 0);
}

TEST(ParametersCount, many_parameters) {
    int result = getMetric<CountParametersMetric>("many_parameters.py");
    EXPECT_EQ(result, 5);
}

TEST(ParametersCount, match_case) {
    int result = getMetric<CountParametersMetric>("match_case.py");
    EXPECT_EQ(result, 1);
}

TEST(ParametersCount, nested_if) {
    int result = getMetric<CountParametersMetric>("nested_if.py");
    EXPECT_EQ(result, 2);
}

TEST(ParametersCount, simple) {
    int result = getMetric<CountParametersMetric>("simple.py");
    EXPECT_EQ(result, 0);
}

TEST(ParametersCount, ternary) {
    int result = getMetric<CountParametersMetric>("ternary.py");
    EXPECT_EQ(result, 1);
}



}  // namespace analyser::metric::metric_impl
