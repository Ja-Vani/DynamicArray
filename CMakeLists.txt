cmake_minimum_required(VERSION 3.29)
project(DynamicArray)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib)
set(gtest_disable_pthreads on)

include_directories(Inc)

add_executable(DynamicArray Src/main.cpp
        Src/my_array.cpp
        Inc/my_array.hpp)

