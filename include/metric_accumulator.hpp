#pragma once
#include <cstddef>
#include <stdexcept>
#include <typeinfo>
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

#include "metric.hpp"

namespace rv = std::ranges::views;
namespace rs = std::ranges;

namespace analyser::metric_accumulator {

struct IAccumulator {
    virtual void Accumulate(const metric::MetricResult &metric_result) = 0;
    virtual void Finalize() = 0;
    virtual void Reset() = 0;
    virtual ~IAccumulator() = default;

protected:
    bool is_finalized = false;
};

struct MetricsAccumulator {
    template <typename Accumulator>
    void RegisterAccumulator(const std::string &metric_name, std::unique_ptr<Accumulator> acc) {
        accumulators[metric_name] = std::move(acc);
    }
    template <typename Accumulator>
    const Accumulator& GetFinalizedAccumulator(const std::string& metric_name) const {
        const Accumulator *result_ptr = dynamic_cast<const Accumulator *>(accumulators.at(metric_name).get());
        if (result_ptr == nullptr) {
            throw std::runtime_error("MetricsAccumulator::GetFinalizedAccumulator(): dynamic_cast failed");
        }
        return *result_ptr;
    }
    void AccumulateNextFunctionResults(const metric::MetricResults &metric_results);

    void ResetAccumulators();

private:
    std::unordered_map<std::string, std::shared_ptr<IAccumulator>> accumulators;
};

}  // namespace analyser::metric_accumulator
