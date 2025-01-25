#include "UseCase.h"

/**
 * NOTE: 具有相互依赖的两个类，将另一个变成内部类，可以解决这个问题
 * 这里 Polygon依赖AABB，将其作为成员属性，然而，AABB同时依赖Polygon，将其作为函数参数，所以是一个相互依赖的关系，这样就需要做成内部类，就可以保证相互之间的依赖关系得到满足
 */

struct Polygon {
    // Define Polygon structure
    std::vector<int> x, y;
    Polygon() {};

    struct AABB {
        // Define AABB structure
        int x1, y1, x2, y2;
        AABB() {};
        AABB(Polygon poly) {
            // Initialize AABB based on Polygon
            x1 = poly.x[0];
            y1 = poly.y[0];
            x2 = poly.x[0];
            y2 = poly.y[0];
        }

    };
    AABB aabb;
};






void inter_dependence () {
    Polygon poly;
    // Add points to polygon
    poly.x = {0, 10, 10, 0};
    poly.y = {0, 0, 10, 10};

    Polygon::AABB aabb;
    std::cout<<"AABB: "<<aabb.x1<<", "<<aabb.y1<<", "<<aabb.x2<<", "<<aabb.y2<<std::endl;

}
