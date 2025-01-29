//
// Created by kang on 2024/7/24.
//

#pragma once

#include <concurrencpp/concurrencpp.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstring>
#include <string>
#include <fstream>

#include <chrono>

#include <cstdlib>
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