#pragma once

#include "function.hpp"
#include "file.hpp"
#include "metric.hpp"

namespace {

analyser::function::Function readFunction(const std::string& filename) {
    analyser::file::File sample_file("/workspaces/module_4_analyser/src/metric_impl/tests/files/" + filename);
    analyser::function::FunctionExtractor f_extractor;
    auto funcs = f_extractor.Get(sample_file);
    return funcs.front();
}

} // anon ns

template<typename MetricT>
int getMetric(const std::string& filename){
    auto func = readFunction(filename);
    MetricT metric_impl;
    return metric_impl.Calculate(func).value;
}