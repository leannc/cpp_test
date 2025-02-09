#include "UseCase.h"
#include <immintrin.h>  // AVX SIMD
#include <vector>
#include <random>
#include <execution>


// 生成随机数填充矩阵
void fill_matrix(std::vector<std::vector<double>>& matrix, uint64_t row, uint64_t col) {  // NOLINT
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++)
      matrix[i][j] = dist(gen);
    }
}

void fill_matrix(std::vector<double>& matrix) {  // NOLINT
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (size_t i = 0; i < matrix.size(); i++)
        matrix[i] = dist(gen);
}

// **基准测试 1：使用 `vector<vector<double>>`**
static void BM_VectorVector_double(benchmark::State& state) {  // NOLINT
    uint64_t row = state.range(0);
    uint64_t col = state.range(1);
    std::vector<std::vector<double>> matrix(row, std::vector<double>(col));
    fill_matrix(matrix, row, col);
    for (auto _ : state) {
        double sum = 0;  // cppcheck-suppress unreadVariable
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                sum += matrix[i][j];  // cppcheck-suppress unreadVariable

      //   benchmark::DoNotOptimize(sum);  // 避免编译器优化
    }
}

// **基准测试 2：使用 `vector<double>`**
void BM_VectorFlat_double(benchmark::State& state) {  // NOLINT
    uint64_t row = state.range(0);
    uint64_t col = state.range(1);
    std::vector<double> matrix(row * col);
    fill_matrix(matrix);
    uint64_t total = row*col;
    for (auto _ : state) {
        double sum = 0;  // cppcheck-suppress unreadVariable
        for (int i = 0; i < total; i++)
                sum += matrix[i];  // cppcheck-suppress unreadVariable

      //   benchmark::DoNotOptimize(sum);
    }
}

void BM_VectorFlat_double_parallel(benchmark::State& state) {  // NOLINT
    uint64_t row = state.range(0);
    uint64_t col = state.range(1);
    std::vector<double> matrix(row * col);
    fill_matrix(matrix);
    uint64_t total = row*col;  // cppcheck-suppress unreadVariable
    for (auto _ : state) {
        double sum = 0;
        std::for_each(std::execution::par, matrix.begin(), matrix.end(), [&sum](const int& element) {
            sum += element;
        });
    }
}

void BM_VectorFlat_double_SIMD(benchmark::State& state) {  // NOLINT
    uint64_t row = state.range(0);
    uint64_t col = state.range(1);
    std::vector<double> matrix(row * col);
    fill_matrix(matrix);
    uint64_t total = row*col;
    for (auto _ : state) {
      __m256d sum_vec = _mm256_setzero_pd();

      int i = 0;
      for (; i+4 < total; i+=4) {
          __m256d data = _mm256_loadu_pd(&matrix[i]);  // 加载 4 个 double 元素到寄存器
          sum_vec = _mm256_add_pd(sum_vec, data);  // 累加
      }

           // 处理剩余的元素
      double partial_sums[4];
      _mm256_storeu_pd(partial_sums, sum_vec);
      double sum = partial_sums[0] + partial_sums[1] + partial_sums[2] + partial_sums[3];  // cppcheck-suppress unreadVariable

      // 处理剩余的元素
      for (; i < matrix.size(); ++i) {
        sum += matrix[i];  // cppcheck-suppress unreadVariable
      }
      //   benchmark::DoNotOptimize(sum);
    }
}


void BM_VectorVector_double_RowMajor(benchmark::State& state) {  // NOLINT
    uint64_t row = state.range(0);
    uint64_t col = state.range(1);
    std::vector<std::vector<double>> matrix(row, std::vector<double>(col));
    fill_matrix(matrix, row, col);
    for (auto _ : state) {
        double sum = 0;  // cppcheck-suppress unreadVariable
        for (int j = 0; j < col; j++)
            for (int i = 0; i < row; i++)
                sum += matrix[i][j];

      //   benchmark::DoNotOptimize(sum);  // 避免编译器优化
    }
}

