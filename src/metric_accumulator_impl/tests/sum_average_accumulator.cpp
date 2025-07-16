#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <gtest/gtest.h>

#include "test_helpers.h"

namespace analyser::metric_accumulator::metric_accumulator_impl::test {

TEST(SumAverageAccumulator, empty) {
    auto accum = getTestAccum<SumAverageAccumulator>(0);
    auto [sum, avrg] = accum.Get();
    EXPECT_EQ(sum, 0);
    EXPECT_EQ(avrg, 0);
}

TEST(SumAverageAccumulator, single) {
    auto accum = getTestAccum<SumAverageAccumulator>(1);
    auto [sum, avrg] = accum.Get();
    EXPECT_EQ(sum, 1);
    EXPECT_EQ(avrg, 1);
}

TEST(SumAverageAccumulator, many) {
    auto accum_10 = getTestAccum<SumAverageAccumulator>(10);
    auto [sum_10, avrg_10] = accum_10.Get();
    EXPECT_EQ(sum_10, 55);
    EXPECT_EQ(avrg_10, 5.5);

    auto accum_1000 = getTestAccum<SumAverageAccumulator>(1000);
    auto [sum_1000, avrg_1000] = accum_1000.Get();
    EXPECT_EQ(sum_1000, 500500);
    EXPECT_EQ(avrg_1000, 500.5);
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl::test
