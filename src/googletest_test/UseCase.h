#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Args;
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::MockFunction;
using ::testing::NiceMock;  // ----这个是suppressing uninteresting calls warnings的，要加上，否则log中会有很多输出
using ::testing::Return;
using ::testing::StrictMock;  // ----这个是把上面的warnings变成errors，直接导致fail

using ::testing::Assign;
using ::testing::SaveArg;

using ::testing::Expectation;
using ::testing::ExpectationSet;
using ::testing::InSequence;
using ::testing::Sequence;

using ::testing::AllOf;  // ----表示的是all of the following matches
using ::testing::AnyOf;
using ::testing::Conditional;  // ---- a short way of writing if-else statement
using ::testing::Contains;     // ----用于vector里面的对比，可以用 vec.Contains(xxx).Times(3); 就是有3个xxx；
using ::testing::ElementsAre;  // ----检查vector中的元素是不是期待的
using ::testing::EndsWith;
using ::testing::Eq;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::MatchesRegex;
using ::testing::Not;
using ::testing::Optional;  // ----可以用于std::optional的相关测试
using ::testing::StartsWith;
using ::testing::UnorderedElementsAre;  // ----不需要顺序的对比，可以用于比较两个container中的内容是否一致
using ::testing::Values;
using ::testing::VariantWith;  // ----可以用于std::variant的相关测试
using ::testing::WhenSorted;   // ----可以给vector排个序

// ----跟指针相关的功能
using ::testing::Address;
using ::testing::Pointee;
using ::testing::Pointer;
