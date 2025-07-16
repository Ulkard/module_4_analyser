#include "metric_accumulator_impl/average_accumulator.hpp"

#include "test_helpers.h"

#include <gtest/gtest.h>

namespace analyser::metric_accumulator::metric_accumulator_impl::test {

TEST(AverageAccumulator, empty) {
    auto accum = getTestAccum<AverageAccumulator>(0);
    EXPECT_DOUBLE_EQ(accum.Get(), 0);
}

TEST(AverageAccumulator, single) {
    auto accum = getTestAccum<AverageAccumulator>(1);
    EXPECT_DOUBLE_EQ(accum.Get(), 1);
}

TEST(AverageAccumulator, many) {
    auto accum_10 = getTestAccum<AverageAccumulator>(10);
    EXPECT_DOUBLE_EQ(accum_10.Get(), 5.5);

    auto accum_1000 = getTestAccum<AverageAccumulator>(1000);
    EXPECT_DOUBLE_EQ(accum_1000.Get(), 500.5);
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl::test
