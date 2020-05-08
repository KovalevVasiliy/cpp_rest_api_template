cmake_minimum_required(VERSION 2.8.12)
project(timer)
set(CMAKE_CXX_STANDARD 17)
include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(timer main.cpp server.cpp server.h)
target_link_libraries(timer ${CONAN_LIBS})