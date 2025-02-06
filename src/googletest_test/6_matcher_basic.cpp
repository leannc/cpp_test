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


TEST(MatchersTest,demo2)
{
    int test_value =10;

    EXPECT_THAT(test_value,AllOf(Gt(0),Lt(100)));
}

TEST(MatchersTest,demo3)
{
    std::string test_string("Hello, this is a test string. We are here to help you!");
    EXPECT_THAT(test_string,StartsWith("Hello"));
    EXPECT_THAT(test_string,EndsWith(". We are here to help you!"));
    EXPECT_THAT(test_string, Not(EndsWith("test string")));
    EXPECT_THAT(test_string, MatchesRegex(".*help you.*"));
}

TEST(MatchersTest,ReferenceTest)
{
    int a =1;
    int& a_ref = a;
    int b=1;

    EXPECT_THAT(a_ref, ::testing::Ref(a));
    EXPECT_THAT(b, Not(::testing::Ref(a)));
}