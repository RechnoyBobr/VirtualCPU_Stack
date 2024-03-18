cmake_minimum_required(VERSION 3.27)
project(CPU_Stack)
set(CMAKE_CXX_STANDARD 20)

add_executable(CPU_Stack main.cxx)

add_subdirectory(stack )
add_subdirectory(Emulator)
target_include_directories(CPU_Stack PRIVATE Emulator/include)
target_include_directories(CPU_Stack PRIVATE stack/include)
include_directories(Emulator/include)
include_directories(stack/include)
target_link_libraries(CPU_Stack PRIVATE emulator preproc)