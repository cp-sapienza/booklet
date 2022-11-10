cmake_minimum_required(VERSION 3.13)

include(GoogleTest)

set(TEST_SOURCES
    test_fenwick.cpp
    test_mod_inverse.cpp
)

add_executable(tests
    ${TEST_SOURCES}
)

target_include_directories(tests
    PUBLIC
        ../source
        ../googletest/include
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_link_libraries(tests
    PUBLIC
        gtest
        gtest_main
)

gtest_discover_tests(tests)
