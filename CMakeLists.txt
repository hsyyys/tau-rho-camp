cmake_minimum_required(VERSION 3.10)
project(trussquad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(trussquad
    main.cpp
    trussquad.cpp
)
