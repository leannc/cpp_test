//
// Created by kang on 2023/12/11.
//

#ifndef CPP_TEST_ANIMAL_H
#define CPP_TEST_ANIMAL_H

/**
 * @author kang
 * @brief 这是一个动物类，作为后面每个具体动物的基类
 * @details 具体信息如下：
 *          1. 它不是一个植物
 *          2. 它能够发出声音
 * */
class Animal
{
public:
    /**
     * 这个是对成员函数的注释
     * */
    virtual void shout();
};


#endif //CPP_TEST_ANIMAL_H
