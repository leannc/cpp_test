//
// Created by wangkang on 2023/11/20.
//
#include <locale.h>

#include "TestInfo.h"
#include "algorithm/UseCase.h"
#include "benchmark/UseCase.h"
#include "boost/UseCase.h"
#include "concurrencpp_test/UseCase.h"
#include "design_pattern/UseCase.h"
#include "entt/UseCase.h"
#include "error_handling/UseCase.h"
#include "general/UseCase.h"
#include "googletest_test/UseCase.h"
#include "numeric/UseCase.h"
#include "performance_engineer/UseCase.h"
#include "sigslot/UseCase.h"
#include "templates/UseCase.h"
#include "templates/template_classes/HideImplementationTemplate.h"
#include "type_traits/UseCase.h"
#include "working_demo_code/UseCase.h"

int main() {
  //---------------------------------------------------
  // CATEGORY   algorithm
  //---------------------------------------------------
  //   CALL_USE_CASE(std_erase);
  // CALL_USE_CASE(std_roate);
  //   CALL_USE_CASE(std_partition);
  //   CALL_USE_CASE(std_transform);
  //   CALL_USE_CASE(std_find);
  //   CALL_USE_CASE(multy_level_sort);
  // CALL_USE_CASE(std_partial_sort);

  //---------------------------------------------------
  // CATEGORY   benchmark
  //---------------------------------------------------
  // BENCHMARK(BM_VectorVector_double)->Args({1, 100000000})->Args({100000000, 1});
  // BENCHMARK(BM_VectorFlat_double)->Args({1000, 10000})->Args({10000, 1000});
  // BENCHMARK(BM_VectorFlat_double_parallel)->Args({1000, 10000})->Args({10000, 1000});
  // BENCHMARK(BM_VectorFlat_double_SIMD)->Args({1000, 10000})->Args({10000, 1000});
  // BENCHMARK(BM_VectorVector_double_RowMajor)->Args({1000, 10000})->Args({10000, 1000});

  // BENCHMARK(BM_HeapContourPoint_traversal)->Args({30, 40, 1000});
  // ->Args({30, 40, 10000000});  // 100万个contour 和 1000万个 contour
  // ->Args({300000, 400000, 100})     // 100万个contour 和 1000万个 contour
  // ->Args({3000000, 4000000, 100});  // 100万个contour 和 1000万个 contour

  // BENCHMARK(BM_CAMContour_Traditional_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_TypeErasure_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_Variant_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_Traditional_ptr_traversal)->Args({40, 40, 1000000});
  // std::cout << "----------sss----------------" << std::endl;
  // BENCHMARK(BM_CAMContour_Traditional_multithread_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_Traditional_multithread_ptr_traversal)->Args({40, 40, 1000000});

  // BENCHMARK(BM_CAMContour_ECS_traversal)->Args({40, 40, 100000});
  // BENCHMARK(BM_CAMContour_Boost_Traditional_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_Unordered_map_Traditional_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_plf_colony_Traditional_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_pure_contour_Traditional_traversal)->Args({40, 40, 1000000});
  // BENCHMARK(BM_CAMContour_Traditional_transform_traversal)->Args({40, 40, 100000});
  // ->Args({30, 40, 10000000});

  // BENCHMARK(BM_HeapContourPoint_traversal_parallel)
  //     ->Args({30, 40, 1000000})
  //     ->Args({30, 40, 10000000});  // 100万个contour 和 1000万个 contour
  // BENCHMARK(BM_HeapContourPoint_traversal_parallel)
  //     ->Args({3, 4, 1000000})
  //     ->Args({3, 4, 10000000});  // 100万个contour 和 1000万个 contour

  // BENCHMARK(BM_with_single_param)->Arg(10000000);  // 有O2编译优化
  // BENCHMARK(BM_without_o2_optimization)->Arg(10000000);  // 没有O2编译优化
  // RUN_BENCH_MARK();

  //---------------------------------------------------
  // CATEGORY   boost
  //---------------------------------------------------
  // CALL_USE_CASE(signals_basic);

  //---------------------------------------------------
  // CATEGORY   concurrencpp
  //---------------------------------------------------
  //   CALL_USE_CASE(concurrencpp_hello_world);
  //   CALL_USE_CASE(concurrencpp_even_number_counting);
  //   CALL_USE_CASE(async_file_processing);
  //   CALL_USE_CASE(async_file_processing_version_2);
  //   CALL_USE_CASE(prime_number_finder);
  //   CALL_USE_CASE(manual_executor);
  //   CALL_USE_CASE(concurrencpp_when_all);
  //   CALL_USE_CASE(concurrencpp_when_any);
  //   CALL_USE_CASE(concurrencpp_result_promise);
  //   CALL_USE_CASE(regular_timer);
  //   CALL_USE_CASE(oneshot_timer);
  //   CALL_USE_CASE(delay_object);
  //   CALL_USE_CASE(concurrencpp_generator);
  //   CALL_USE_CASE(concurrencpp_async_locks);
  // CALL_USE_CASE(async_condition_variable_test);
  //   CALL_USE_CASE(SLA_axis_init);

  //---------------------------------------------------
  // CATEGORY   design_pattern
  //---------------------------------------------------
  // CALL_USE_CASE(visitor_pattern_in_std_variant_form);
  //   CALL_USE_CASE(strategy_pattern_combine_with_visitor_pattern);
  //   CALL_USE_CASE(strategy_using_template_params);
  //   CALL_USE_CASE(observer_using_std_function);
  //   CALL_USE_CASE(concepts_can_replace_inheritance);
  //   CALL_USE_CASE(concepts_can_replace_inheritance_advanced);
  //   CALL_USE_CASE(pimple_bridge_pattern);
  //   CALL_USE_CASE(typical_prototype_pattern);
  //   CALL_USE_CASE(external_polymorphism_pattern);
  //   CALL_USE_CASE(owning_type_erasure_implementation);
  // CALL_USE_CASE(cam_component_type_erasure_implementation);
  //   CALL_USE_CASE(classic_decorator_design_pattern);
  //   CALL_USE_CASE(compile_time_decorator);
  //   CALL_USE_CASE(value_based_run_time_decorator);
  //   CALL_USE_CASE(singleton_with_dependency_injection);

  //---------------------------------------------------
  // CATEGORY   entt
  //---------------------------------------------------
  // CALL_USE_CASE(entt_basic_view);
  // CALL_USE_CASE(entt_reactive_storage);
  // CALL_USE_CASE(entt_ctx);
  // CALL_USE_CASE(entt_snapshot);
  // CALL_USE_CASE(entt_snapshot_with_cereal);
  // CALL_USE_CASE(entt_serialize_pointer);
  // CALL_USE_CASE(entt_copy_entity);
  // CALL_USE_CASE(entt_copy_to_another_registry);
  // CALL_USE_CASE(entt_multy_same_component_type);
  // CALL_USE_CASE(entt_view_with_iterator);
  // CALL_USE_CASE(entt_runtime_view);
  // CALL_USE_CASE(entt_group);
  // CALL_USE_CASE(entt_tag);
  // CALL_USE_CASE(entt_runtime_unique_sequential_identifier);

  //---------------------------------------------------
  // CATEGORY   error_handling
  //---------------------------------------------------
  //   CALL_USE_CASE(output_log_should_in_caller);
  //   CALL_USE_CASE(use_optional_to_convey_error_info);
  //   CALL_USE_CASE(use_errno_to_convey_different_errors);
  //   CALL_USE_CASE(custom_std_error_code);
  //   CALL_USE_CASE(use_std_variant_as_return_error_info_container);
  //   CALL_USE_CASE(use_expected);
  // CALL_USE_CASE(monadic_operation);

  //---------------------------------------------------
  // CATEGORY   general
  //---------------------------------------------------
  //   CALL_USE_CASE(std_variant_with_visitor2);
  //   CALL_USE_CASE(std_variant_with_visitor3);
  //   CALL_USE_CASE(std_variant_with_visitor4);
  //   CALL_USE_CASE(std_variant_with_template);
  //   CALL_USE_CASE(polymorphism_do_things_in_base_constructor);
  //   CALL_USE_CASE(polymorphism_dynamic_registry);
  //   CALL_USE_CASE(std_set_test);
  //   CALL_USE_CASE(std_min_max_element_test);
  //   CALL_USE_CASE(semaphore_test);
  CALL_USE_CASE(condition_variable_test);
  //   CALL_USE_CASE(std_async_simple_test);
  //   CALL_USE_CASE(std_async_complex_1_test);
  //   CALL_USE_CASE(std_function_as_a_parameter_test);
  //   CALL_USE_CASE(std_for_each_test);
  // CALL_USE_CASE(std_unique_ptr);
  // CALL_USE_CASE(std_span);
  //   CALL_USE_CASE(std_string_view);
  //   CALL_USE_CASE(std_move);
  //   CALL_USE_CASE(std_decay);
  //   CALL_USE_CASE(noexcept_usage);
  // CALL_USE_CASE(std_unique_ptr_with_custom_deleter);
  // CALL_USE_CASE(std_unique_ptr_custom_deleter_should_call_delete_raw_ptr_inside);
  //   CALL_USE_CASE(std_format);
  //   CALL_USE_CASE(std_atomic);
  //   CALL_USE_CASE(inter_dependence);
  //   CALL_USE_CASE(customize_unordered_map);
  //   CALL_USE_CASE(customize_std_map);
  // CALL_USE_CASE(data_type_overflow);
  // CALL_USE_CASE(function_object);
  // CALL_USE_CASE(lambda_closure);
  // CALL_USE_CASE(customize_iterator);
  // CALL_USE_CASE(std_view_filter);
  // CALL_USE_CASE(cereal_test);
  //---------------------------------------------------
  // CATEGORY   numeric
  //---------------------------------------------------
  // CALL_USE_CASE(std_inner_product);

  //---------------------------------------------------
  // CATEGORY   performance
  //---------------------------------------------------
  //   CALL_USE_CASE(packing_and_encoding);

  //---------------------------------------------------
  // CATEGORY   sigslot
  //---------------------------------------------------
  // CALL_USE_CASE(signal_basic);
  // CALL_USE_CASE(signal_with_param);
  // CALL_USE_CASE(multi_thread_signal_slot);

  //---------------------------------------------------
  // CATEGORY   templates
  //---------------------------------------------------
  //   CALL_USE_CASE(hide_implementation_template_use);
  //   CALL_USE_CASE(variadic_template_use);
  //   CALL_USE_CASE(variadic_function_template);
  //   CALL_USE_CASE(stand_alone_fold_expression_using);
  //   CALL_USE_CASE(parameter_pack_expansion_and_perfect_forwarding);
  //   CALL_USE_CASE(abbreviation_template);
  //   CALL_USE_CASE(concept_test);
  //   CALL_USE_CASE(concept_requirements_test);
  //   CALL_USE_CASE(template_function_overload);

  //---------------------------------------------------
  // CATEGORY   type_traits
  //---------------------------------------------------
  //   CALL_USE_CASE(std_is_same_v);
  //   CALL_USE_CASE(std_decay_t);
  //   CALL_USE_CASE(function_return_values_in_type_traits);
  //   CALL_USE_CASE(std_declval);

  //---------------------------------------------------
  // CATEGORY   working_demo_code
  //---------------------------------------------------
  // CALL_USE_CASE(split_contour_for_fabric_cutting);
  return 0;
}
