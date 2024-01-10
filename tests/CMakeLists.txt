find_package(GTest REQUIRED)

add_executable(ssolve_tests)
target_sources(ssolve_tests PRIVATE fake_test.cpp)

target_link_libraries(ssolve_tests PRIVATE GTest::gtest_main)
