//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/15
//
#include "../SortTestHelper.h"
#include "../SortingBasis.h"

int main() {
    int n = 50000;
    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 0);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("mergeSort", mergeSort, arr, n);
    SortTestHelper::testSort("insertionSort", insertionSort, arr2, n);
    SortTestHelper::testSort("insertionSortImprove", insertionSortImprove, arr3, n);
    SortTestHelper::testSort("mergeSortBottomUp", mergeSortBottomUp, arr4, n);

    delete (arr);  // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr2); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr3); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr4); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    return 0;
}