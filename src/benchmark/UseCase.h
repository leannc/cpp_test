//
// Created by kang on 2024/7/24.
//

#include <benchmark/benchmark.h>

#define RUN_BENCH_MARK()                                                \
    char arg0_default[] = "benchmark";                                  \
    char* args_default = arg0_default;                                  \
    int argc = 1;                                                       \
    char**  argv = &args_default;                                       \
    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks();                              \
    ::benchmark::Shutdown();                                            \


void BM_string_compare(benchmark::State& state);
void BM_with_single_param(benchmark::State& state);
void BM_with_multy_param(benchmark::State& state);
void BM_without_o2_optimization(benchmark::State& state);