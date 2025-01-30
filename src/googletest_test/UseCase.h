#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::AllOf;  //----表示的是all of the following matches
using ::testing::Gt;
using ::testing::Lt;
using ::testing::MatchesRegex;
using ::testing::StartsWith;
using ::testing::Contains; //----用于vector里面的对比，可以用 vec.Contains(xxx).Times(3); 就是有3个xxx；
using ::testing::EndsWith;
using ::testing::Not;
using ::testing::Values;
using ::testing::Optional;  //----可以用于std::optional的相关测试
using ::testing::VariantWith;  //----可以用于std::variant的相关测试
using ::testing::Conditional; //---- a short way of writing if-else statement
using ::testing::ElementsAre; //----检查vector中的元素是不是期待的
using ::testing::UnorderedElementsAre; //----不需要顺序的对比，可以用于比较两个container中的内容是否一致
using ::testing::WhenSorted; //----可以给vector排个序

//----跟指针相关的功能
using ::testing::Pointer; 
using ::testing::Pointee; 
using ::testing::Address; 