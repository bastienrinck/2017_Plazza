cmake_minimum_required(VERSION 3.9)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_plazza
        src/main_cli.cpp
        src/plazza.cpp src/plazza.hpp)
