add_subdirectory(parser)
add_subdirectory(preprocessor)

add_library(emulator emulator.cxx)
target_include_directories(emulator PRIVATE include)
include_directories(include)
target_link_libraries(emulator PRIVATE stack)
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
add_executable(emulator_tests tests/tests.cxx)
target_link_libraries(emulator_tests GTest::gtest_main)
gtest_discover_tests(emulator_tests)
