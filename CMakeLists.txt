cmake_minimum_required(VERSION 3.17)
project(tee)

set(CMAKE_CXX_STANDARD 14)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(tee src/main.cpp
        src/Tee.hpp
        src/Tee.cpp
        src/line.hpp
        src/settings.cpp
        src/settings.hpp)

target_link_libraries(tee ${CONAN_LIBS})