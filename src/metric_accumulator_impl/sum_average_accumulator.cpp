#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

namespace analyser::metric_accumulator::metric_accumulator_impl {

void SumAverageAccumulator::Accumulate(const metric::MetricResult& metric_result)  {
    sum += metric_result.value;
    ++count;
}

void SumAverageAccumulator::Finalize() {
    average = count == 0 ? 0 : static_cast<double>(sum)/count;
}

void SumAverageAccumulator::Reset() {
    sum = 0;
    count = 0;
    average = 0;
}

SumAverageAccumulator::SumAverage SumAverageAccumulator::Get() const {
    return {sum, average};
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl
