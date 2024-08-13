cmake_minimum_required(VERSION 3.28)
project(MPointer)

set(CMAKE_CXX_STANDARD 17)

add_executable(MPointer main.cpp
        MPointer.h
        MPointerGC.cpp
        MPointerGC.h

)
