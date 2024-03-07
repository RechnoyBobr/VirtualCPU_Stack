cmake_minimum_required(VERSION 3.27)
project(CPU_Stack)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(stack)

add_subdirectory(Emulator)

add_executable(CPU_Stack main.cxx)
target_link_libraries(CPU_Stack PRIVATE emulator)