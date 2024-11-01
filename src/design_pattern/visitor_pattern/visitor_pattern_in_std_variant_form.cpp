//
// Created by kang on 2023/11/21.
//

#include "../UseCase.h"

//------------------------------powerful--------------------------------
class Circle {
public:
   void DrawCircle() const {std::cout<<"circle"<<std::endl;}
};

class Box {
public:
    void DrawBox() const {std::cout<<"box"<<std::endl;}
};

class Square {
public:
    void DrawSquare() const {std::cout<<"square"<<std::endl;}
};

class Other {
public:
    void DrawOther() const {std::cout<<"other"<<std::endl;}
};

class Other2 {
public:
    void DrawOther() const {std::cout<<"other2"<<std::endl;}
};


class Draw
{
public:
    void operator()(Circle & c) {c.DrawCircle();}
    void operator()(Box & b) {b.DrawBox();}
    void operator()(Square & s) {s.DrawSquare();}
    void operator()(auto & s) {s.DrawOther();}  //默认参数，如果没有匹配的，就调用这个
};

using Shape = std::variant<Circle,Box,Square,Other,Other2>;

void visitor_pattern_in_std_variant_form() {
    std::vector<Shape> variant_list = {Circle{},Other2{}, Box{},Square{},Other{}};

    for (auto &variant: variant_list) {
        ///这里用std::visit来写
        std::visit(Draw{}, variant);
    }
}

//-------------------pointer version-------------------------------------
class Draw2
{
public:
    void operator()(Circle* c) {c->DrawCircle();}
    void operator()(Box* b) {b->DrawBox();}
    void operator()(Square* s) {s->DrawSquare();}
};

using ShapePointer = std::variant<Circle*,Box*,Square*>;

void visitor_pattern_in_std_variant_form_pointer_version() {
    Circle c;
    Box b;
    Square s;
    std::vector<ShapePointer> variant_pointer_list = { &c,&b,&s};

    for (auto &variant: variant_pointer_list) {
        ///这里用std::visit来写
        std::visit(Draw2{}, variant);
    }
}