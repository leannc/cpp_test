#include "UseCase.h"


class TestFixture_demo : public ::testing::Test {
  protected:

  static void SetUpTestSuite() {
    // Code here will be called before the first test
    // in this test suite.
    std::cout << "====================================Testsuite setup ================================" << std::endl;
  }

  static void TearDownTestSuite() {
    // Code here will be called after the last test
    // in this test suite.
    std::cout << "====================================Testsuite teardown =============================" << std::endl;
  }

  void SetUp() override {
    // Code here will be called immediately before each test.
    std::cout << "Testing fixture set up." << std::endl;
  }
  void TearDown() override {
    // Code here will be called immediately after each test.
    std::cout << "Testing fixture tear down." << std::endl;
  }
};

TEST_F(TestFixture_demo, test1) {
  ASSERT_NEAR(1.220,1.221,0.1);
}

TEST_F(TestFixture_demo, test2) {
  ASSERT_NEAR(1.223,1.221,0.1);
}

TEST_F(TestFixture_demo, DISABLED_test3) {
  std::cout << "This test is disabled and this line should not be printed." << std::endl;
}

TEST_F(TestFixture_demo, test4) {
  GTEST_SKIP() << "test4 is skipped.";
  std::cout << "This test is skipped and this line should not be printed." << std::endl;
}