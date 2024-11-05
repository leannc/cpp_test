cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
project(CPP_TEST)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/general/UseCase.h
        src/general/std_variant_with_visitor.cpp
        src/general/polymorphism_dynamic_registry.cpp
        src/general/polymorphism_do_things_in_base_constructor.cpp
        src/templates/template_classes/HideImplementationTemplate.cpp
        src/templates/template_classes/HideImplementationTemplate.h
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
        src/concurrencpp_test/8_when_any.cpp
        src/concurrencpp_test/9_result_promise.cpp
        src/concurrencpp_test/10_regular_timer.cpp
        src/concurrencpp_test/11_oneshot_timer.cpp
        src/concurrencpp_test/12_delay_object.cpp
        src/concurrencpp_test/13_generator.cpp
        src/concurrencpp_test/14_async_locks.cpp
        src/concurrencpp_test/15_async_condition_variable.cpp
        src/concurrencpp_test/16_SLA_axis_init.cpp
        src/templates/hide_implementation_template_use.cpp
        src/templates/template_classes/VariadicClassTemplate.cpp
        src/templates/template_classes/VariadicClassTemplate.h
        src/templates/variadic_template_use.cpp
        src/templates/VariadicFuntionTemplate.cpp

        src/templates/stand_alone_fold_expression.cpp
        src/templates/abbreviation_template.cpp
        src/general/std_min_max_element.cpp
        src/general/std_function_as_a_parameter.cpp
        src/templates/concepts.cpp
        src/templates/concept_requirements.cpp
        src/general/std_for_each.cpp

        src/design_pattern/visitor_pattern/visitor_pattern_in_std_variant_form.cpp
        src/design_pattern/strategy_pattern/strategy_pattern_combine_with_visitor_pattern.cpp
        src/design_pattern/observer_pattern/observer_using_std_function.cpp

        src/general/std_unique_ptr.cpp
        src/design_pattern/strategy_pattern/strategy_using_template_params.cpp
        src/general/std_span.cpp
        src/algorithm/std_erase.cpp
        src/general/std_string_view.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC src/concurrencpp_test/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
        src/concurrencpp_test/lib
)

target_link_libraries(${PROJECT_NAME} concurrencpp)