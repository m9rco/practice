cmake_minimum_required(VERSION 3.5)
project(Algorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#=====================================================================@
add_executable(bos0 basis/0.os/IOSelect.cpp)
add_executable(bos1 basis/0.os/IOBlock.cpp)
add_executable(bos2 basis/0.os/IONonBlock.cpp)

#=====================================================================@
add_executable(m sort.cpp)


add_executable(bso0 basis/3.sorting/BubbleSort.cpp)
add_executable(bso1 basis/3.sorting/InsertionSort.cpp)
add_executable(bso2 basis/3.sorting/SelectionSort.cpp)
add_executable(bso3 basis/3.sorting/MergeSort.cpp)
add_executable(bso4 basis/3.sorting/ShellSort.cpp)
add_executable(bso5 basis/3.sorting/QuickSort.cpp)
add_executable(bso6 basis/3.sorting/HeapSort.cpp)


add_executable(bse0 basis/4.search/BinarySearch.cpp)
add_executable(bse1 basis/4.search/BinarySearchTree.cpp)
add_executable(bse2 basis/4.search/SequenceSearchTree.cpp)

add_executable(bun0 basis/5.union-find/UnionFindForSize.cpp)
add_executable(bun1 basis/5.union-find/UnionFindForRank.cpp)
add_executable(bun2 basis/5.union-find/UnionFindForPathCompression.cpp)

add_executable(bgr0 basis/6.graph/DenseGraph.cpp)
add_executable(bgr1 basis/6.graph/SparseGraph.cpp)
add_executable(bgr2 basis/6.graph/ReadGraph.cpp)
add_executable(bgr3 basis/6.graph/Components.cpp)
add_executable(bgr4 basis/6.graph/Edge.cpp)

add_executable(solution0 solution/AccessLog.cpp)
add_executable(solution1 solution/Defense.cpp)
add_executable(solution2 solution/RSA.cpp)
add_executable(solution3 solution/ArrayOperation.cpp)
add_executable(solution4 solution/MonsterDrink.cpp)
add_executable(solution5 solution/ApplyFund.cpp)
add_executable(solution6 solution/SlowCrawler.cpp)
add_executable(solution7 solution/IntegerSequence.cpp)
add_executable(solution8 solution/KLevelStage.cpp)

add_executable(leetcode151 leetcode/_151_ReverseWords.cpp)
add_executable(leetcode283 leetcode/_283_MoveZeroes.cpp)
add_executable(leetcode887 leetcode/_887_SuperEggDrop.cpp)