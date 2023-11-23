cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
project(CPP_TEST)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/general/UseCase.h
        src/general/std_variant_with_visitor.cpp
        src/general/polymorphism_dynamic_registry.cpp
        src/general/polymorphism_do_things_in_base_constructor.cpp
)