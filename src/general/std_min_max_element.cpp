//
// Created by kang on 2024/10/28.
//
#include "UseCase.h"

struct Point
{
    int x;
    int y;
};

void std_min_max_element_test()
{
    std::vector<Point> list={{3,4},{5,6},{2,7},{1,4}};

    auto target = std::min_element(std::begin(list),std::end(list),[](const Point& a, const Point& b){
        return a.y<b.y;
    });

    Point result = *target;
    int index = std::distance(list.begin(),target);

    std::cout<<"result is "<<result.x<<" , "<<result.y<<"; index is "<<index<<std::endl;


    //==============max=======

    auto max_target= std::max_element(std::begin(list),std::end(list),[](const Point& a, const Point& b){
        return a.x<b.x;
    });

    int max_index = std::distance(list.begin(),max_target);
    Point max_result = *max_target;

    std::cout<<"max_result is "<<max_result.x<<" , "<<max_result.y<<"; max_index is "<<max_index<<std::endl;

}