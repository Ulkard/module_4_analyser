#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"

namespace analyser {

namespace rv = std::ranges::views;

using SingleAnalyseResult =  std::pair<function::Function, metric::MetricResults>;
using AnalyseResult = std::vector<SingleAnalyseResult>;

AnalyseResult AnalyseFunctions(const std::vector<std::string>& files,
                      const analyser::metric::MetricExtractor& metric_extractor) {
    auto functions = files | rv::transform([](const std::string& filename) {
        static function::FunctionExtractor f_extractor;
        return f_extractor.Get(file::File(filename));
    }); 
    auto metrics = functions | rv::join | rv::transform([&metric_extractor](auto&& f){
        return metric_extractor.Get(f);
    });

    AnalyseResult result;
    std::ranges::for_each(rv::zip(functions | rv::join, metrics), [&result](SingleAnalyseResult&& sr){
        result.emplace_back(sr.first, sr.second);
    });

    return result;
}

auto SplitByClasses(const AnalyseResult& analysis) {
    return analysis | rv::filter([](const SingleAnalyseResult& sr) {
        return sr.first.class_name.has_value();
    }) | rv::chunk_by([](auto&& lhs, auto&& rhs){
        return *lhs.first.class_name == *rhs.first.class_name; 
    });
}

auto SplitByFiles(const AnalyseResult& analysis) {
    return analysis | rv::chunk_by([](auto&& lhs, auto&& rhs){
        return lhs.first.filename == rhs.first.filename;
    });
}

void AccumulateFunctionAnalysis(
    const auto& analysis, analyser::metric_accumulator::MetricsAccumulator& accumulator) {
    std::ranges::for_each(analysis, [&accumulator](const SingleAnalyseResult& sr){
        accumulator.AccumulateNextFunctionResults(sr.second);
    });
}

} // namespace analyser
