# Common library
add_library(common INTERFACE)
target_include_directories(common INTERFACE common)

# Test executable
add_executable(test_order
    tests/test_order.cpp
)
target_link_libraries(test_order PRIVATE common)
