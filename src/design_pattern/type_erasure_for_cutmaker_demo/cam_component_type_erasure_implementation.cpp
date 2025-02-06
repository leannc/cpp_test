//
// Created by kang on 2024/11/9.
//

#include "CAMComponent.h"


struct MicroLink {
    double microlink_p1;
    std::string microlink_name;
};

struct CoolPoint {
    double coolPoint_p1;
    int coolPoint_p2;
};

struct StartPoint {
    int start_p1;
};



void cam_component_type_erasure_implementation() {
    auto mk_updater = [](MicroLink const& m) {std::cout<< "micro_link p1:"<< m.microlink_p1<< ", p2:"<< m.microlink_name<< std::endl;};
    auto cp_updater = [](CoolPoint const& c) {std::cout<< "cool_point p1 "<< c.coolPoint_p1<< ", p2:"<< c.coolPoint_p2<< std::endl;};
    auto st_updater = [](StartPoint const& s) {std::cout<< "start_point p1 "<< s.start_p1<< std::endl;};

    MicroLink micro_link(1.0, "micro_link_1");
    CoolPoint cool_point(2.0, 56);
    StartPoint start_point(111);

    std::vector<CAMComponent> components;

    CAMComponent mircro_link_component(micro_link, mk_updater);
    CAMComponent cool_point_component(cool_point, cp_updater);
    CAMComponent start_point_component(start_point, st_updater);

    components.push_back(mircro_link_component);
    components.push_back(cool_point_component);
    components.push_back(start_point_component);

    for (auto& component : components) {
        component.update();
    }
}
