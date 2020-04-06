cmake_minimum_required(VERSION 3.5)
project(Algorithm)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES basis/4.search/BinarySearch.cpp)
#set(SOURCE_FILES basis/4.search/Test.cpp)

add_executable(bso0 basis/3.sorting/BubbleSort.cpp)
add_executable(bso1 basis/3.sorting/InsertionSort.cpp)
add_executable(bso2 basis/3.sorting/SelectionSort.cpp)
add_executable(bso3 basis/3.sorting/MergeSort.cpp)
add_executable(bso4 basis/3.sorting/ShellSort.cpp)
add_executable(bso5 basis/3.sorting/QuickSort.cpp)

add_executable(bse0 basis/4.search/BinarySearch.cpp)
add_executable(bse1 basis/4.search/BinarySearchTree.cpp)
add_executable(bse2 basis/4.search/SequenceSearchTree.cpp)