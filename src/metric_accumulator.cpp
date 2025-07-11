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
    for (const auto& m_result : metric_results) {
        if (!accumulators.contains(m_result.metric_name)) {
            throw std::invalid_argument(std::format("accumulator {} not found", m_result.metric_name));
        } 
        accumulators[m_result.metric_name]->Accumulate(m_result);
    }
}

void MetricsAccumulator::ResetAccumulators() {
    std::ranges::for_each(accumulators, [](auto& accum){
        accum.second->Reset();
    });
}

}  // namespace analyser::metric_accumulator
