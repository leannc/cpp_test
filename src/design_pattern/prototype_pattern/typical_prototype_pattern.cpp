//
// Created by kang on 2024/11/2.
//
#include "../UseCase.h"
#include <set>


class Animal {
public:
    virtual ~Animal() =default;
    virtual void makeSound() const =0;
    virtual std::unique_ptr<Animal> clone() const =0;  ///proto type design pattern
};


class Sheep : public Animal {
public:
    explicit Sheep(std::string name_):name(std::move(name_)) {}

    void makeSound() const override { std::cout<<"baaaa"<<std::endl;}

    std::unique_ptr<Animal> clone() const override { return std::make_unique<Sheep>(*this);} ///调用自己的copy construct，生成一个sheep

private:
    std::string name;
};


void typical_prototype_pattern()
{
    std::unique_ptr<Animal>  dolly = std::make_unique<Sheep>("Dolly");
    std::unique_ptr<Animal> dollyClone = dolly->clone();

    dollyClone->makeSound();


}