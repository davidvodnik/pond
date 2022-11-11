cmake_minimum_required(VERSION 3.15)

project(Pond LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/glew-cmake)
add_subdirectory(src)
