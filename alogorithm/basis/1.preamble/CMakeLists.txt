cmake_minimum_required(VERSION 3.9)

# 项目名
project(example)

#add_subdirectory(example_01)

set(CMAKE_C_STANDARD 99)

# 查找当前目录下的所有源文件
aux_source_directory(./example_01 DIR_SRCS)

# 指定生成目标
add_executable(OpenCVGrad ${DIR_SRCS})
#add_executable(OpenCVGrad example_02.c)
