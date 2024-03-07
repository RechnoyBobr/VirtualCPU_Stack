add_subdirectory(parser)
add_subdirectory(preprocessor)

add_library(emulator emulator.cxx)
include_directories(include)
target_link_libraries(emulator PRIVATE stack)
