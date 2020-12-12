cmake_minimum_required(VERSION 3.17)
project(GraphicsEngine3D)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
add_executable(vector.h vector.cpp matrix.h matrix.cpp main.cpp camera.h camera.cpp)
