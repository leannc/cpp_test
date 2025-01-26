cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
project(CPP_TEST)

add_executable(${PROJECT_NAME}
        src/main.cpp

        src/general/UseCase.h
        src/general/std_variant_with_visitor.cpp
        src/general/polymorphism_dynamic_registry.cpp
        src/general/polymorphism_do_things_in_base_constructor.cpp
        src/general/std_set.cpp
        src/general/semaphore_test.cpp
        src/general/condition_variable.cpp
        src/general/std_async_simple.cpp
        src/general/std_async_complex_1.cpp
        src/general/std_min_max_element.cpp
        src/general/std_function_as_a_parameter.cpp
        src/general/std_for_each.cpp
        src/general/std_move.cpp
        src/general/std_unique_ptr.cpp
        src/general/std_span.cpp  
        src/general/std_string_view.cpp
        src/general/std_variant_with_template.cpp
        src/general/std_decay.cpp
        src/general/noexcept_usage.cpp
        src/general/std_unique_ptr_with_custom_deleter.cpp
        src/general/std_format.cpp
        src/general/std_atomic.cpp
        src/general/inter_dependence.cpp
        src/general/customize_unordered_map.cpp

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
        src/templates/template_classes/HideImplementationTemplate.cpp
        src/templates/template_classes/HideImplementationTemplate.h
        src/templates/concepts.cpp
        src/templates/concept_requirements.cpp
        src/templates/template_function_overload.cpp
        
        src/design_pattern/strategy_pattern/strategy_using_template_params.cpp
        src/design_pattern/visitor_pattern/visitor_pattern_in_std_variant_form.cpp
        src/design_pattern/strategy_pattern/strategy_pattern_combine_with_visitor_pattern.cpp
        src/design_pattern/observer_pattern/observer_using_std_function.cpp
        src/design_pattern/concepts_over_CRTP/concepts_can_replace_inheritance.cpp
        src/design_pattern/concepts_over_CRTP/concepts_can_replace_inheritance_advanced.cpp
        src/design_pattern/bridge_pattern/car.cpp
        src/design_pattern/bridge_pattern/car.h
        src/design_pattern/bridge_pattern/pimple_bridge_pattern.cpp
        src/design_pattern/prototype_pattern/typical_prototype_pattern.cpp
        src/design_pattern/external_polymorphism_pattern/ShapeConcept.h
        src/design_pattern/external_polymorphism_pattern/ShapeModel.h
        src/design_pattern/external_polymorphism_pattern/external_polymorphism_pattern.cpp
        src/design_pattern/owning_type_erasure_implementation/owning_type_erasure_implementation.cpp
        src/design_pattern/owning_type_erasure_implementation/Shape.h
        src/design_pattern/decorator_pattern/classic/classic_decorator_design_pattern.cpp
        src/design_pattern/decorator_pattern/ConferenceTicket.h
        src/design_pattern/decorator_pattern/compile_time_decorator_pattern/Decorators.h
        src/design_pattern/decorator_pattern/compile_time_decorator_pattern/compile_time_decorator.cpp
        src/design_pattern/decorator_pattern/value_based_run_time_decorator_pattern/Items.h
        src/design_pattern/decorator_pattern/value_based_run_time_decorator_pattern/Decorators.h
        src/design_pattern/decorator_pattern/value_based_run_time_decorator_pattern/value_based_run_time_decorator.cpp
        src/design_pattern/singleton_pattern/persistenceInterface.h
        src/design_pattern/singleton_pattern/database.h
        src/design_pattern/singleton_pattern/persistenceInterface.cpp
        src/design_pattern/singleton_pattern/singleton_with_dependency_injection.cpp



        src/type_traits/std_is_same_v.cpp
        src/type_traits/std_decay_t.cpp
        src/type_traits/std_declval.cpp
        src/type_traits/function_return_values_in_type_traits.cpp

        src/algorithm/std_erase.cpp
        src/algorithm/std_find.cpp
        src/algorithm/multy_level_sort.cpp
        src/algorithm/std_roate.cpp
        src/algorithm/std_partition.cpp
        src/algorithm/std_transform.cpp

        
        "src/performance engineer/packing_and_encoding.cpp"

)

target_include_directories(${PROJECT_NAME}
    PUBLIC src/concurrencpp_test/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
        src/concurrencpp_test/lib
)

target_link_libraries(${PROJECT_NAME} concurrencpp)