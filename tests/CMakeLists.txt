find_package(GTest REQUIRED)

add_executable(ssolve_tests)
target_sources(
  ssolve_tests PRIVATE test_board.cpp test_tile.cpp test_index.cpp
                       test_is_valid.cpp test_matrix.cpp test_valid_options.cpp)

target_link_libraries(ssolve_tests PRIVATE ssolve_impl GTest::gmock_main)
