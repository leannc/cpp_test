#include "UseCase.h"
#include <algorithm>

// 定义一个map，key是测试用例的名字，value是测试用例的输入数据
std::map<std::string, std::vector<int>> input_map = {
    {"sorted", {1, 2, 3}}, {"reverse_sorted", {3, 2, 1}}, {"all_same", {1, 1, 1}}};

// 定义一个参数化的testsuite，参数是测试用例的名称和输入数据
class SortTestSuite : public testing::TestWithParam<std::pair<const std::string, std::vector<int>>> {};

// 注册参数化testsuite
INSTANTIATE_TEST_SUITE_P(SortTestSuite_Demo, SortTestSuite, ::testing::ValuesIn(input_map),
                         [](const testing::TestParamInfo<SortTestSuite::ParamType> &info) { return info.param.first; });

// 定义一个测试函数，参数是测试用例的名称
TEST_P(SortTestSuite, TestSort) {
  std::vector<int> v = GetParam().second;

  std::sort(v.begin(), v.end());

  for (size_t i = 0; i < v.size() - 1; ++i) {
    EXPECT_LE(v[i], v[i + 1]);
  }
}

TEST_P(SortTestSuite, TestSort2) {
  std::vector<int> v = GetParam().second;

  std::sort(v.begin(), v.end());

  for (size_t i = 0; i < v.size() - 1; ++i) {
    EXPECT_LE(v[i], v[i + 1]);
  }
}
