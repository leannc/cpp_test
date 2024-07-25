cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
project(CPP_TEST)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/general/UseCase.h
        src/general/std_variant_with_visitor.cpp
        src/general/polymorphism_dynamic_registry.cpp
        src/general/polymorphism_do_things_in_base_constructor.cpp
        src/templates/MyTemplate.cpp
        src/templates/MyTemplate.h
        src/general/std_set.cpp

        src/general/semaphore_test.cpp
        src/general/condition_variable.cpp
        src/general/std_async_simple.cpp
        src/general/std_async_complex_1.cpp

        src/doxygen_test/Animal.cpp
        src/doxygen_test/Animal.h
        src/doxygen_test/Animal.h
        src/doxygen_test/Cat.cpp
        src/doxygen_test/Cat.h
        src/concurrencpp_test/1_concurrencpp_hello_world.cpp
        src/concurrencpp_test/UseCase.h
        src/concurrencpp_test/2_concurrencpp_even_number_counting.cpp
        src/concurrencpp_test/3_async_file_processing.cpp
        src/concurrencpp_test/4_async_file_processing_version_2.cpp
        src/concurrencpp_test/5_prime_number_finder.cpp
        src/concurrencpp_test/6_manual_executor.cpp
        src/concurrencpp_test/7_when_all.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC src/concurrencpp_test/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
        src/concurrencpp_test/lib
)

target_link_libraries(${PROJECT_NAME} concurrencpp)