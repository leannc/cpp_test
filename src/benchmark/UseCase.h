#pragma once
// Created by kang on 2024/7/24.
//

#include <benchmark/benchmark.h>

#define RUN_BENCH_MARK()                                                                                               \
  char arg0_default[] = "benchmark";                                                                                   \
  char* args_default = arg0_default;                                                                                   \
  int argc = 1;                                                                                                        \
  char** argv = &args_default;                                                                                         \
  ::benchmark::Initialize(&argc, argv);                                                                                \
  if (::benchmark::ReportUnrecognizedArguments(argc, argv))                                                            \
    return 1;                                                                                                          \
  ::benchmark::RunSpecifiedBenchmarks();                                                                               \
  ::benchmark::Shutdown();

void BM_string_compare(benchmark::State& state);           // NOLINT
void BM_with_single_param(benchmark::State& state);        // NOLINT
void BM_with_multy_param(benchmark::State& state);         // NOLINT
void BM_without_o2_optimization(benchmark::State& state);  // NOLINT

void BM_VectorVector_double(benchmark::State& state);                             // NOLINT
void BM_VectorFlat_double(benchmark::State& state);                               // NOLINT
void BM_VectorFlat_double_parallel(benchmark::State& state);                      // NOLINT
void BM_VectorFlat_double_SIMD(benchmark::State& state);                          // NOLINT
void BM_VectorVector_double_RowMajor(benchmark::State& state);                    // NOLINT
void BM_HeapContourPoint_traversal(benchmark::State& state);                      // NOLINT
void BM_HeapContourPoint_traversal_parallel(benchmark::State& state);             // NOLINT
void BM_CAMContour_Boost_Traditional_traversal(benchmark::State& state);          // NOLINT
void BM_CAMContour_Unordered_map_Traditional_traversal(benchmark::State& state);  // NOLINT
void BM_CAMContour_plf_colony_Traditional_traversal(benchmark::State& state);     // NOLINT

void BM_CAMContour_Traditional_traversal(benchmark::State& state);      // NOLINT
void BM_CAMContour_Traditional_ptr_traversal(benchmark::State& state);  // NOLINT

void BM_CAMContour_Traditional_multithread_traversal(benchmark::State& state);      // NOLINT
void BM_CAMContour_Traditional_multithread_ptr_traversal(benchmark::State& state);  // NOLINT

void BM_CAMContour_Traditional_transform_traversal(benchmark::State& state);     // NOLINT
void BM_CAMContour_pure_contour_Traditional_traversal(benchmark::State& state);  // NOLINT

void BM_CAMContour_ECS_traversal(benchmark::State& state);  // NOLINT
