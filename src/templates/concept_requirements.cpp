//
// Created by kang on 2024/10/30.
//

#include "UseCase.h"

template<typename T>
concept Doc = requires(T t, int b) {
        t.exportToJSON();
        t.serialize(b);
};

void useDoc (Doc auto d)
{
    std::cout<<"calling useDoc"<<std::endl;
    d.exportToJSON();
}

class Good
{
public:
    int exportToJSON() {return 0;};
    void serialize( int b) {};
};

class Bad
{
public:
    void exportToJSON() {};
    void serialize( std::string b) {};
};


void concept_requirements_test()
{

    useDoc(Good{});
//    useDoc(Bad{});  ///报错，因为没有满足require的要求

}