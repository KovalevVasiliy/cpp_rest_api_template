cmake_minimum_required(VERSION 2.8.12)
project(server)
set(CMAKE_CXX_STANDARD 17)
include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(server main.cpp server.cpp server.h)
target_link_libraries(server ${CONAN_LIBS})