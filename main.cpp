#include <memory>
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

#include "analyse.hpp"
#include "cmd_options.hpp"
#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"
#include "metric_accumulator_impl/accumulators.hpp"
#include "metric_accumulator_impl/categorical_accumulator.hpp"
#include "metric_accumulator_impl/sum_average_accumulator.hpp"
#include "metric_impl/code_lines_count.hpp"
#include "metric_impl/cyclomatic_complexity.hpp"
#include "metric_impl/metrics.hpp"

using namespace analyser;
using namespace metric_accumulator::metric_accumulator_impl;

void printAnalyseResults(const auto& results) {
    for(const auto& [func, m_results] : results){
        std::println("{}{}::{}", 
            func.filename, 
            func.class_name ? "::"+*func.class_name : "", 
            func.name);
        for(const auto& [name, value] : m_results) {
            std::println("    {}: {}", name, value);
        }
    }
    std::println();
}

void printAccumulator(const metric_accumulator::MetricsAccumulator& accum) {
    auto lines_count_accum = accum.GetFinalizedAccumulator<SumAverageAccumulator>("CodeLinesCount");
    lines_count_accum.Finalize();
    std::println("    CodeLinesCount avrg: {:.1f}", lines_count_accum.Get().average);
    std::println("    CodeLinesCount sum : {}", lines_count_accum.Get().sum);

    auto complexity_accum = accum.GetFinalizedAccumulator<SumAverageAccumulator>("CyclomaticComplexity");
    complexity_accum.Finalize();
    std::println("    CyclomaticComplexity avrg: {:.1f}", complexity_accum.Get().average);
    std::println("    CyclomaticComplexity sum : {}", complexity_accum.Get().sum);

    auto param_count_accum = accum.GetFinalizedAccumulator<AverageAccumulator>("CountParameters");
    param_count_accum.Finalize();
    std::println("    CountParameters avrg: {}", param_count_accum.Get());
    std::println();
}

int main(int argc, char *argv[]) {
    analyser::cmd::ProgramOptions options;
    options.Parse(argc, argv);

    metric::MetricExtractor metric_extractor;

    // зарегистрируйте метрики в metric_extractor
    using namespace metric::metric_impl;
    metric_extractor.RegisterMetric(std::make_unique<CodeLinesCountMetric>());
    metric_extractor.RegisterMetric(std::make_unique<CyclomaticComplexityMetric>());
    metric_extractor.RegisterMetric(std::make_unique<CountParametersMetric>());

    auto analyse_result = analyser::AnalyseFunctions(options.GetFiles(), metric_extractor);
    printAnalyseResults(analyse_result);

    metric_accumulator::MetricsAccumulator accumulator;

    // зарегистрируйте аккумуляторы метрик в accumulator
    accumulator.RegisterAccumulator("CodeLinesCount", std::make_unique<SumAverageAccumulator>());
    accumulator.RegisterAccumulator("CyclomaticComplexity", std::make_unique<SumAverageAccumulator>());
    accumulator.RegisterAccumulator("CountParameters", std::make_unique<AverageAccumulator>());

    auto file_splitted = SplitByFiles(analyse_result);
    for (const auto& res : file_splitted ) {
        std::println("Accumulated Analysis for file {}:", res.front().first.filename);
        AccumulateFunctionAnalysis(res, accumulator);
        printAccumulator(accumulator);
    }

    // reset reset accumulators
    accumulator.ResetAccumulators();
    accumulator.RegisterAccumulator("CodeLinesCount", std::make_unique<SumAverageAccumulator>());
    accumulator.RegisterAccumulator("CyclomaticComplexity", std::make_unique<SumAverageAccumulator>());
    accumulator.RegisterAccumulator("CountParameters", std::make_unique<AverageAccumulator>());

    auto class_splitted = SplitByClasses(analyse_result);
    for (const auto& res : class_splitted ) {
        std::println("Accumulated Analysis for class {}:", *res.front().first.class_name);
        AccumulateFunctionAnalysis(res, accumulator);
        printAccumulator(accumulator);
    }

    return 0;
}
