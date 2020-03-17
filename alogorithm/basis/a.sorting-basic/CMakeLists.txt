cmake_minimum_required(VERSION 3.5)
project(SortBasis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES selection-sort/main.cpp)
#set(SOURCE_FILES bubble-sort/main.cpp)
#set(SOURCE_FILES shell-sort/main.cpp )
#set(SOURCE_FILES merge-sort/main.cpp)

#set(SOURCE_FILES merge-sort-bottom-up/main.cpp )
set(SOURCE_FILES quick-sort/main.cpp )
add_executable(SortBasis ${SOURCE_FILES})