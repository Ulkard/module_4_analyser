#include "metric_accumulator.hpp"
#include "metric.hpp"

#include <stdexcept>
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

void MetricsAccumulator::AccumulateNextFunctionResults(const metric::MetricResults &metric_results) {
    std::ranges::for_each(metric_results, [&](const metric::MetricResult& m_result) {
        const auto iter = accumulators.find(m_result.metric_name);
        if (iter == accumulators.end()) {
            throw std::invalid_argument(std::format("accumulator {} not found", m_result.metric_name));
        } 
        iter->second->Accumulate(m_result);
    });
}

void MetricsAccumulator::ResetAccumulators() {
    std::ranges::for_each(accumulators, [](auto &accum) { accum.second->Reset(); });
}

}  // namespace analyser::metric_accumulator
