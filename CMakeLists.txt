cmake_minimum_required(VERSION 3.9)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(cpp_plazza
        src/main_cli.cpp
        src/plazza.cpp
        src/plazza.hpp
        src/threadz.cpp
        src/threadz.hpp src/slave.cpp src/slave.hpp src/threadzPool.cpp src/threadzPool.hpp src/slavePool.cpp src/slavePool.hpp)
