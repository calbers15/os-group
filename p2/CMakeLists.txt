##Cameron Albers & Austin Silva
##EECE.4811 - Operating Systems
##Michael J. Geiger, Yongshun Xu
##Project 2 - Multithreading

cmake_minimum_required(VERSION 3.10)

project(p2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(p2 
    main.c
    prod_cons_MT.c
    prod_cons_MT.h
)


target_compile_options(p2 PRIVATE -Wall -Wextra -pthread -lpthread)