add_library(preproc preprocessor.cxx)
target_include_directories(preproc PRIVATE include)
include_directories(include)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(preproc stack)
enable_testing()
include(GoogleTest)
add_executable(preproc_tests tests/tests_preproc.cxx)
target_link_libraries(preproc_tests GTest::gtest_main)
gtest_discover_tests(preproc_tests)
