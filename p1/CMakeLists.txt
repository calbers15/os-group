cmake_minimum_required(VERSION 3.10)

project(ind_proj_1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ind_proj_1 
    ind_proj_1.cpp
)

target_compile_options(ind_proj_1 PRIVATE -Wall -Wextra)