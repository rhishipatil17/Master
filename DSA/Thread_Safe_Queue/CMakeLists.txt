cmake_minimum_required(VERSION 3.14)
project(ThreadSafeQueue)

find_package(Threads REQUIRED)

add_library(tsq_lib INTERFACE)
target_include_directories(tsq_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(tsq_lib INTERFACE cxx_std_20)
target_link_libraries(tsq_lib INTERFACE Threads::Threads)

option(BUILD_TESTS "Build tests for tsq_lib" ON)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_executable(tsq_lib_tests thread_safe_queue_test.cpp)
    target_link_libraries(tsq_lib_tests 
        PRIVATE 
            tsq_lib 
            GTest::gtest_main
    )

    set_target_properties(tsq_lib_tests PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests"
    )

    include(GoogleTest)
    gtest_discover_tests(tsq_lib_tests)
endif()
