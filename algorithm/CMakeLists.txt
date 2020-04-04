cmake_minimum_required(VERSION 3.5)
project(Algorithm)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES basis/4.search/BinarySearch.cpp)
#set(SOURCE_FILES basis/4.search/Test.cpp)

add_executable(bse0 basis/4.search/BinarySearch.cpp)
add_executable(bse1 basis/4.search/BinarySearchTree.cpp)
add_executable(bse2 basis/4.search/SequenceSearchTree.cpp)