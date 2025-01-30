#include "UseCase.h"


TEST(MatchersTest,SimpleMatcherExpectThat)
{
    ::testing::Matcher<int> is_one = 1;
    ::testing::Matcher<int> is_zero = 0;
    ::testing::Matcher<bool> is_true = true;

    EXPECT_THAT(1, is_one);
    EXPECT_THAT(2-2, is_zero);
    EXPECT_THAT(true, is_true);
}