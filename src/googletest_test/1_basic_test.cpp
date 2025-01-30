#include "UseCase.h"


TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, BasicAssertions2) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  EXPECT_TRUE(false);
  EXPECT_STREQ("hello", "world");
}


TEST(FloatingTest, test1) {
  // Expect two strings not to be equal.
  EXPECT_DOUBLE_EQ(2.223,2.221);

}

TEST(FloatingTest, test2) {

  ASSERT_NEAR(1.223,1.221,0.1);

}

TEST(FloatingTest, test3) {

  ASSERT_NEAR(1.220,1.221,0.1);

}