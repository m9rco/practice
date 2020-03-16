//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/15
//
#include "../SortTestHelper.h"
#include "../SortingBasis.h"

int main() {
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);

    selectionSort(arr, n);
    insertionSort(arr2, n);
    insertionSortImprove(arr3, n);

    SortTestHelper::testSort("selectionSort", selectionSort, arr, n);
    SortTestHelper::testSort("insertionSort", insertionSort, arr2, n);
    SortTestHelper::testSort("insertionSortImprove", insertionSortImprove, arr3, n);
    delete (arr);
    delete (arr2);
    delete (arr3);
    return 0;
}



