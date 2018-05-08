cmake_minimum_required(VERSION 3.9)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(cpp_plazza
        src/main_gui.cpp
        src/Plazza.cpp
        src/Plazza.hpp
        src/Thread.cpp
        src/Thread.hpp
        src/ThreadPool.cpp
        src/ThreadPool.hpp
        src/GuiManager.hpp
        src/GuiManager.cpp src/datatype.hpp)
