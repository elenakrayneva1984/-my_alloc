cmake_minimum_required(VERSION 3.2)

set(This allocator_test)

set(Sources
    allocator_test.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    my_alloc
)
add_test(
    NAME ${This}
    COMMAND ${This}
)