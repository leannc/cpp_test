#include "UseCase.h"

uint64_t Increment(uint64_t n) {
  uint64_t sum = 0;
  for (uint64_t i = 0; i < n; i++) {
    sum++;
  }
  return sum;
}

uint64_t Increment_without_optimization(uint64_t n) {
  uint64_t sum = 0;
  for (uint64_t i = 0; i < n; i++) {
    benchmark::DoNotOptimize(sum++);
    benchmark::ClobberMemory();
  }
  return sum;
}

void BM_with_single_param(benchmark::State &state) {  // NOLINT
  for (auto _ : state) {
    Increment(state.range(0));
  }
  state.SetComplexityN(state.range(0));
}

void BM_without_o2_optimization(benchmark::State &state) {  // NOLINT
  for (auto _ : state) {
    Increment_without_optimization(state.range(0));
  }
  state.SetComplexityN(state.range(0));
}

void BM_with_multy_param(benchmark::State &state) {  // NOLINT
  for (auto _ : state) {
    int i1 = state.range(0);
    int i2 = state.range(1);
    auto sum = i1 + i2;
  }
}
