cmake_minimum_required(VERSION 3.9)

# 项目名
project(basis)

set(CMAKE_C_STANDARD 99)

# 把 src 作为子 module
add_subdirectory(1.preamble)
add_subdirectory(2.linear_table)
add_subdirectory(3.stack_and_queue)
add_subdirectory(4.string)
add_subdirectory(5.array_and_lists)

aux_source_directory(. DIR_SRCS)