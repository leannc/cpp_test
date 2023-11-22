//
// Created by kang on 2023/11/21.
//
#include "UseCase.h"

class base
{
public:
    void shout()
    {
        std::cout<<this->name()<<" shouted"<<std::endl;
    };

    virtual std::string name() = 0;
};

class dog : public base
{
    std::string name() override
    {
        return "dog";
    }
};

class cat : public base
{
    std::string name() override
    {
        return "cat";
    }
};



void polymorphism()
{
    std::vector<base*> animals;
    animals.push_back(new dog());
    animals.push_back(new cat());

    for(auto animal : animals)
    {
        animal->shout();
    }
}