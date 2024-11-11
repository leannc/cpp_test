//
// Created by kang on 2024/11/7.
//

#include "../UseCase.h"
#include <type_traits>

/**
 * 这个版本和上一个版本相比，主要是非侵入式地继承:
 * 1.在定义concept的时候，相比于直接使用std::is_base_of，间接地用了一个子类模板IsShape，去继承它，实现这个的功能。
 * 2.在定义完rectangle以后，将IsShape模板特化，使它总是返回true，告诉编译器，它就是这个子类。
 * 3.通过这种方式，实现了跟继承类似的效果，但是！再也没有vtable了，直接被concept定义好了
 * */

struct ShapeBase{};

template<typename T>
struct IsShape : public std::is_base_of<ShapeBase,T> {};

template<typename T>
concept Shape =
    requires (T t){
        {t.area()} ->std::same_as<decltype(t.perimeter())>;  ///area()函数的返回值，需要与perimeter()函数的返回值类型相同
        //{t.area()} ->std::same_as<decltype(T::radius)>;  ///area()函数的返回值，需要与radius成员变量的类型相同
    }
    && IsShape<T>::value;

template<Shape S>
auto printArea(S s) {
    std::cout<<"the area is "<<s.area()<<std::endl;
    return;
}


template<typename Unit>
class Circle : private ShapeBase{
public:
    Circle(Unit radius_) :radius(radius_) {};

    double area() {return radius*radius*3.14;}

public:
    Unit perimeter() { return 2*radius*3.14;};
    Unit radius;
};



template<typename Unit>
class Rectangle  {
public:
    Rectangle(Unit length_,Unit width_) :length(length_),width(width_) {};

    double area() {return length*width;}

public:
    Unit perimeter() { return 2*(length + width);};
    Unit length;
    Unit width;
};

template<typename Unit>
struct IsShape<Rectangle<Unit>> : public std::true_type {};




void concepts_can_replace_inheritance_advanced() {
    printArea(Circle<double>{0.5});  ///可以，因为都是double
//    printArea(Circle<int>{5});  ///报错，因为不满足 std::same_as<decltype(t.perimeter())>; 这个返回值的条件，需要area()函数和perimeter()成员函数的返回值类型相同

    printArea(Rectangle<double>{5,10});  ///可以，因为特化了IsShape这个template，让它的Rectangle场景返回true。
}