#pragma once

#include "metric.hpp"
#include <cstddef>
#include <ranges>

namespace {

inline auto makeMetricResults(size_t size) {
    return std::views::iota(1) |
           std::views::transform([](int val) { return analyser::metric::MetricResult{"", val}; }) |
           std::views::take(size);
}

}  // namespace

template <typename AccumT>
AccumT getTestAccum(size_t size) {
    AccumT accum;
    std::ranges::for_each(makeMetricResults(size), [&accum](auto &&mr) { accum.Accumulate(mr); });
    accum.Finalize();
    return accum;
}