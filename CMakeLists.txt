cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
project(CPP_TEST)

add_executable(${PROJECT_NAME})
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.h)
target_sources(${PROJECT_NAME} PUBLIC ${sources})


set(PCH_HEADER "src/pch.h")
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_HEADER})

target_include_directories(${PROJECT_NAME}
    PUBLIC src/concurrencpp_test/include
    PUBLIC $ENV{HERA_WORKSPACE_DIR}/Dependencies/expected/include
#     PUBLIC libs/google_benchmark/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
        src/concurrencpp_test/lib/${LIB_TYPE_DIR_NAME}
        # libs/google_benchmark/${LIB_TYPE_DIR_NAME}
        # libs/google_benchmark/${LIB_TYPE_DIR_NAME}
)

set(benchmark_DIR "$ENV{HERA_WORKSPACE_DIR}/HeraBinaries/benchmark/${LIB_TYPE_DIR_NAME}/lib/cmake/benchmark")
find_package(benchmark REQUIRED)

set(GTest_DIR "$ENV{HERA_WORKSPACE_DIR}/HeraBinaries/googletest/${LIB_TYPE_DIR_NAME}/lib/cmake/GTest")
find_package(GTest REQUIRED)


# target_link_libraries(${PROJECT_NAME} concurrencpp)
target_link_libraries(${PROJECT_NAME} concurrencpp GTest::gtest_main GTest::gmock_main benchmark::benchmark)