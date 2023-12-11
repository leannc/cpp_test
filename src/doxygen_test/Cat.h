//
// Created by kang on 2023/12/11.
//

#ifndef CPP_TEST_CAT_H
#define CPP_TEST_CAT_H

#include "Animal.h"

/**
 * @author wangkang
 * @brief 这是一个猫
 * @details 详细描述
 *          1. 可以发出喵喵声
 * */
class Cat : public Animal
{
public:
    void shout() override;
};
#endif //CPP_TEST_CAT_H
