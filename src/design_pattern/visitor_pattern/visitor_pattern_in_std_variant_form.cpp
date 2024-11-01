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

class Draw
{
public:
    void operator()(Circle & c) {c.DrawCircle();}
    void operator()(Box & b) {b.DrawBox();}
    void operator()(Square & s) {s.DrawSquare();}
};

using Shape = std::variant<Circle,Box,Square>;

void visitor_pattern_in_std_variant_form() {
    std::vector<Shape> variant_list = {Circle{}, Box{},Square{}};

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