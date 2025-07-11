#include "metric_impl/parameters_count.hpp"
#include "test_helpers.h"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(ParametersCount, simple) {
    int result = getMetric<CountParametersMetric>("simple.py");
    EXPECT_EQ(result, 0);
}

TEST(ParametersCount, many_parameters) {
    int result = getMetric<CountParametersMetric>("many_parameters.py");
    EXPECT_EQ(result, 5);
}

TEST(ParametersCount, comments) {
    int result = getMetric<CountParametersMetric>("comments.py");
    EXPECT_EQ(result, 3);
}

}  // namespace analyser::metric::metric_impl
