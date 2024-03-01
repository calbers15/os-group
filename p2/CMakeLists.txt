cmake_minimum_required(VERSION 3.10)

project(p2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(p2 
    main.c
)


target_compile_options(p1 PRIVATE -Wall -Wextra)