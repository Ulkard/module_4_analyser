#include "metric_accumulator_impl/average_accumulator.hpp"

#include <stdexcept>
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

void AverageAccumulator::Accumulate(const metric::MetricResult& metric_result)  {
    if (is_finalized) {
        throw std::logic_error("Accumulate() on finalized Accumulator");
    }
    sum += metric_result.value;
    ++count;
}

void AverageAccumulator::Finalize() {
    is_finalized = true;
    average = count == 0 ? 0 : static_cast<double>(sum)/count;
}

void AverageAccumulator::Reset() {
    is_finalized = false;
    sum = 0;
    count = 0;
    average = 0;
}

double AverageAccumulator::Get() const {
    if (is_finalized) {
        return average;
    } else {
        throw std::logic_error("Get() on unfinalized Accumulator");
    }
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl
