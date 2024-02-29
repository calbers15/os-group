cmake_minimum_required(VERSION 3.10)

project(p1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(p1 
    main.c
)
add_executable(t1
    test1.c
)
add_executable(t2
    test2.c
)
add_executable(t3
    test3.c
)
add_executable(t4
    test4.c
)
add_executable(t5
    test5.c
)


target_compile_options(p1 PRIVATE -Wall -Wextra)