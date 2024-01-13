add_library(ssolve_impl OBJECT)
target_include_directories(ssolve_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(ssolve_impl PUBLIC cxx_std_20)
target_sources(
  ssolve_impl PRIVATE solve.cpp types/board.cpp solve/solve_impl.cpp
                      solve/adjacency_matrix.cpp solve/valid_options.cpp)

add_executable(ssolve)
target_sources(ssolve PRIVATE main.cpp)
target_link_libraries(ssolve PRIVATE ssolve_impl)
