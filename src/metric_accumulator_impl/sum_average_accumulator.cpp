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
    if (is_finalized) {
        throw std::logic_error("Accumulate() on finalized Accumulator");
    }
    sum += metric_result.value;
    ++count;
}

void SumAverageAccumulator::Finalize() {
    is_finalized = true;
    average = count == 0 ? 0 : static_cast<double>(sum)/count;
}

void SumAverageAccumulator::Reset() {
    is_finalized = false;
    sum = 0;
    count = 0;
    average = 0;
}

SumAverageAccumulator::SumAverage SumAverageAccumulator::Get() const {
    if (is_finalized) {
        return {sum, average};
    } else {
        throw std::logic_error("Get() on unfinalized Accumulator");
    }
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl
