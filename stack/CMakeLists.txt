
add_library(stack INTERFACE include/stack.h)

# GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)
add_executable(stack_tests test/tests_stack.cxx)
target_link_libraries(stack_tests GTest::gtest_main)
gtest_discover_tests(stack_tests)

