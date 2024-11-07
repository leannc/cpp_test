//
// Created by kang on 2024/11/7.
//

#include "../UseCase.h"
#include <type_traits>

struct ShapeBase{};


template<typename T>
concept Shape =
    requires (T t){
        {t.area()} ->std::same_as<decltype(t.perimeter())>;  ///area()函数的返回值，需要与perimeter()函数的返回值类型相同
        //{t.area()} ->std::same_as<decltype(T::radius)>;  ///area()函数的返回值，需要与radius成员变量的类型相同
    }
    && std::is_base_of_v<ShapeBase,T>;

template<Shape S>
auto printArea(S s) {
    std::cout<<"the area is "<<s.area();
    return;
}


template<typename Unit>
class Circle : private ShapeBase{
public:
    Circle(Unit radius_) :radius(radius_) {};

    double area() {return radius*radius*3.14;}

private:
    Unit perimeter() { return 2*radius*3.14;};
    Unit radius;
};


template<typename Unit>
class Rectangle  {
public:
    Rectangle(Unit length_,Unit width_) :length(length_),width(width_) {};

    double area() {return length*width;}

private:
    Unit perimeter() { return 2*(length + width);};
    Unit length;
    Unit width;
};





void concepts_can_replace_inheritance() {
    printArea(Circle<double>{5});  ///可以，因为都是double
//    printArea(Circle<int>{5});  ///报错，因为不满足 std::same_as<decltype(t.perimeter())>; 这个返回值的条件，需要area()函数和perimeter()成员函数的返回值类型相同

//    printArea(Rectangle<double>{5});  ///报错，因为不满足 std::is_base_of_v<ShapeBase,T>; 需要是ShapeBase的子类才行
}