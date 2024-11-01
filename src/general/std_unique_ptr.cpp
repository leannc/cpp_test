//
// Created by kang on 2024/11/1.
//

#include "UseCase.h"

class DrawStrategy
{
public:
    virtual void draw() = 0;
    virtual ~DrawStrategy()=default;
};

class OpenGLDrawer : public DrawStrategy
{
public:
    void draw() override {std::cout<<"using opengl drawer"<<std::endl;};
};



class Circle
{
public:
    Circle(double radius_,std::unique_ptr<DrawStrategy>& drawer_):radius(radius_),drawer(std::move(drawer_)) {};

    void draw() {drawer->draw();}

private:
    double radius;
    std::unique_ptr<DrawStrategy> drawer;
};



void std_unique_ptr()
{
    std::unique_ptr<DrawStrategy> drawer = std::make_unique<OpenGLDrawer>();

    if(drawer.get() == nullptr)
    {
        std::cout << "empty before"<<std::endl;
    }
    else
    {
        std::cout<<"the pointer address is "<<drawer.get()<<std::endl;
    }

    Circle c(2.3,drawer);
    c.draw();

    if(drawer.get() == nullptr)
    {
        std::cout << "empty now"<<std::endl;
    }


}