#pragma once
#include <unistd.h>

#include <string>
#include "metric.hpp"

namespace analyser::metric::metric_impl {

struct CodeLinesCountMetric final: IMetric {
private:
    MetricResult::ValueType CalculateImpl(const function::Function& f) const override;
    std::string Name() const override;
};

} // namespace analyser::metric::metric_impl
