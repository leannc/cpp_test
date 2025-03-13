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
    PUBLIC $ENV{HERA_WORKSPACE_DIR}/Dependencies/sigslot/include
    PUBLIC $ENV{HERA_WORKSPACE_DIR}/Dependencies/entt/single_include/entt
    PUBLIC $ENV{HERA_WORKSPACE_DIR}/Dependencies/cereal/include
    # PUBLIC "E:/Syncthing/libs/boost_1_76_0/"
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

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_THROW_EXCEPTION_DISABLE)

set(Boost_NO_BOOST_CMAKE ON)
set(Boost_NO_SYSTEM_PATHS ON)
# set(BOOST_INCLUDEDIR "E:/Syncthing/libs/boost_1_76_0/")
find_package(Boost REQUIRED COMPONENTS exception)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_directories(${PROJECT_NAME} PUBLIC ${Boost_LIBRARY_DIRS})
    message("boost libraries : " ${Boost_LIBRARIES})
    # target_link_libraries(${PROJECT_NAME} 
    # libboost_atomic-vc143-mt-gd-x64-1_87
    # libboost_charconv-vc143-mt-gd-x64-1_87
    # libboost_chrono-vc143-mt-gd-x64-1_87
    # libboost_container-vc143-mt-gd-x64-1_87
    # libboost_context-vc143-mt-gd-x64-1_87
    # libboost_contract-vc143-mt-gd-x64-1_87
    # libboost_coroutine-vc143-mt-gd-x64-1_87
    # libboost_date_time-vc143-mt-gd-x64-1_87
    # libboost_exception-vc143-mt-gd-x64-1_87
    # libboost_fiber-vc143-mt-gd-x64-1_87
    # libboost_filesystem-vc143-mt-gd-x64-1_87
    # libboost_graph-vc143-mt-gd-x64-1_87
    # libboost_iostreams-vc143-mt-gd-x64-1_87
    # libboost_json-vc143-mt-gd-x64-1_87
    # libboost_locale-vc143-mt-gd-x64-1_87
    # libboost_log_setup-vc143-mt-gd-x64-1_87
    # libboost_log-vc143-mt-gd-x64-1_87
    # libboost_math_c99f-vc143-mt-gd-x64-1_87
    # libboost_math_c99l-vc143-mt-gd-x64-1_87
    # libboost_math_c99-vc143-mt-gd-x64-1_87
    # libboost_math_tr1f-vc143-mt-gd-x64-1_87
    # libboost_math_tr1l-vc143-mt-gd-x64-1_87
    # libboost_math_tr1-vc143-mt-gd-x64-1_87
    # libboost_nowide-vc143-mt-gd-x64-1_87
    # libboost_prg_exec_monitor-vc143-mt-gd-x64-1_87
    # libboost_process-vc143-mt-gd-x64-1_87
    # libboost_program_options-vc143-mt-gd-x64-1_87
    # libboost_python312-vc143-mt-gd-x64-1_87
    # libboost_random-vc143-mt-gd-x64-1_87
    # libboost_regex-vc143-mt-gd-x64-1_87
    # libboost_serialization-vc143-mt-gd-x64-1_87
    # libboost_stacktrace_from_exception-vc143-mt-gd-x64-1_87
    # libboost_stacktrace_noop-vc143-mt-gd-x64-1_87
    # libboost_stacktrace_windbg_cached-vc143-mt-gd-x64-1_87
    # libboost_stacktrace_windbg-vc143-mt-gd-x64-1_87
    # libboost_system-vc143-mt-gd-x64-1_87
    # libboost_test_exec_monitor-vc143-mt-gd-x64-1_87
    # libboost_thread-vc143-mt-gd-x64-1_87
    # libboost_timer-vc143-mt-gd-x64-1_87
    # libboost_type_erasure-vc143-mt-gd-x64-1_87
    # libboost_unit_test_framework-vc143-mt-gd-x64-1_87
    # libboost_url-vc143-mt-gd-x64-1_87
    # libboost_wave-vc143-mt-gd-x64-1_87
    # libboost_wserialization-vc143-mt-gd-x64-1_87
    # )
endif()


# target_link_libraries(${PROJECT_NAME} concurrencpp)
target_link_libraries(${PROJECT_NAME} concurrencpp GTest::gtest_main GTest::gmock_main benchmark::benchmark Boost::exception)