#include "UseCase.h"

MATCHER(IsEvenKang, "failed in kang's custom failling message") { return (arg % 2) == 0; }

TEST(CustomMatcher, IsEvenKangMatcherTest) {
  EXPECT_THAT(10, IsEvenKang());
  EXPECT_THAT(10, Not(IsEvenKang()));
}

MATCHER_P2(IsBetweenKang, a, b, "") { return a <= arg && arg <= b; }

TEST(CustomMatcher, IsBetweenKangMatcherTest) { EXPECT_THAT(10, IsBetweenKang(9, 11)); }
