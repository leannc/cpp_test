#include "UseCase.h"
#include <algorithm>

// 定义一个map，key是测试用例的名字，value是测试用例的输入数据
std::map<std::string, std::vector<int>> input_map2 = {
    {"sorted", {1, 2, 3}}, {"reverse_sorted", {3, 2, 1}}, {"all_same", {1, 1, 1}}};

void SelectionSort(std::vector<int> &input) { std::sort(input.begin(), input.end()); }

void BubbleSort(std::vector<int> &input) { std::sort(input.begin(), input.end()); }

std::map<std::string, std::function<void(std::vector<int> &)>> function_map = {{"SelectionSort", SelectionSort},
                                                                               {"Bubble", BubbleSort}};

// 定义一个参数化的testsuite，参数是测试用例的名称和输入数据
class CombinedSortTestSuite
    : public testing::TestWithParam<std::tuple<std::pair<const std::string, std::function<void(std::vector<int> &)>>,
                                               std::pair<const std::string, std::vector<int>>>> {};

// 注册参数化测试用例
INSTANTIATE_TEST_SUITE_P(SortTestSuite_Demo2, CombinedSortTestSuite,
                         ::testing::Combine(::testing::ValuesIn(function_map), ::testing::ValuesIn(input_map2)),
                         [](const testing::TestParamInfo<CombinedSortTestSuite::ParamType> &info) {
                           return std::get<0>(info.param).first + "_" + std::get<1>(info.param).first;
                         });

TEST_P(CombinedSortTestSuite, CombineSort) {
  auto p = GetParam();
  auto SortFunction = std::get<0>(p).second;
  auto input = std::get<1>(p).second;

  SortFunction(input);
  for (size_t i = 0; i < input.size() - 1; ++i) {
    EXPECT_LE(input[i], input[i + 1]);
  }
}
