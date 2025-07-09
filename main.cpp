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

#include "analyse.hpp"
#include "cmd_options.hpp"
#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"
#include "metric_accumulator_impl/accumulators.hpp"
#include "metric_impl/metrics.hpp"

int main(int argc, char *argv[]) {
    //analyser::cmd::ProgramOptions options;
    analyser::file::File sample_file("../files/sample.py");
    analyser::function::FunctionExtractor f_extractor;
    auto funcs = f_extractor.Get(sample_file);

    for (const auto& f: funcs) {
        std::println("{}::{}\n{}\n\n", f.class_name ? *f.class_name : "", f.name, f.ast);
    }
    // analyser::metric::MetricExtractor metric_extractor;
    // зарегистрируйте метрики в metric_extractor

    // запустите analyser::AnalyseFunctions
    // выведете результаты анализа на консоль

    // analyser::metric_accumulator::MetricsAccumulator accumulator;
    // зарегистрируйте аккумуляторы метрик в accumulator

    // запустите analyser::SplitByFiles
    // запустите analyser::AccumulateFunctionAnalysis для каждого подмножества результатов метрик
    // выведете результаты на консоль

    // запустите analyser::SplitByClasses
    // запустите analyser::AccumulateFunctionAnalysis для каждого подмножества результатов метрик
    // выведете результаты на консоль

    // запустите analyser::AccumulateFunctionAnalysis для всех результатов метрик
    // выведете результаты на консоль

    return 0;
}
