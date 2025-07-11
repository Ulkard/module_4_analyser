#include "metric_accumulator.hpp"
#include "metric.hpp"

#include <unistd.h>

#include <algorithm>
#include <any>
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

namespace analyser::metric_accumulator {

void MetricsAccumulator::AccumulateNextFunctionResults(const metric::MetricResults &metric_results) const {
    std::ranges::for_each(accumulators, [&metric_results](auto& accum){
        std::ranges::for_each(metric_results, [&accum](const auto& metric_result) {
            accum.second->Accumulate(metric_result);
        });
    });
}

void MetricsAccumulator::ResetAccumulators() {
    std::ranges::for_each(accumulators, [](auto& accum){
        accum.second->Reset();
    });
}

}  // namespace analyser::metric_accumulator
