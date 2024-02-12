cmake_minimum_required(VERSION 3.10)

project(p1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(p1 
    main.c
)

target_compile_options(p1 PRIVATE -Wall -Wextra)