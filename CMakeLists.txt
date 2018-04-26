cmake_minimum_required(VERSION 3.9)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(cpp_plazza
        src/main_cli.cpp
        src/plazza.cpp
        src/plazza.hpp
        src/threadz.cpp
        src/threadz.hpp)
