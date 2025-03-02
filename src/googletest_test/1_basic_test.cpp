#include "UseCase.h"

TEST(basic_test, test1) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(basic_test, test2) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  EXPECT_TRUE(false);
  EXPECT_STREQ("hello", "world");
}

TEST(basic_test, test3) {
  // Expect two strings not to be equal.
  EXPECT_DOUBLE_EQ(2.223, 2.221);
}

TEST(basic_test, test4) { ASSERT_NEAR(1.223, 1.221, 0.1); }

TEST(basic_test, test5) { ASSERT_NEAR(1.220, 1.221, 0.1); }
