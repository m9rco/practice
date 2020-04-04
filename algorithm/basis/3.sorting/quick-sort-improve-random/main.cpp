//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/18
//
#include "../SortTestHelper.h"
#include "../SortingBasis.h"

int main() {
    int n = 50000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("quickSort", quickSort, arr, n);
    SortTestHelper::testSort("quickSortImproveInsertion", quickSortImproveInsertion, arr2, n);
    SortTestHelper::testSort("quickSortImproveRandom", quickSortImproveRandom, arr3, n);

    delete (arr);  // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr2); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr3); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    cout << "\n>> nearly ordered array \n\n";
    int *arrc = SortTestHelper::generateNearlyOrderedArray(n, 100);
    int *arrc2 = SortTestHelper::copyIntArray(arrc, n);
    int *arrc3 = SortTestHelper::copyIntArray(arrc, n);

    // 在近乎有序的数组传过去的时候  快排会变成 O(n^2) 的
    SortTestHelper::testSort("quickSort", quickSort, arr, n);
    SortTestHelper::testSort("quickSortImproveInsertion", quickSortImproveInsertion, arrc2, n);
    SortTestHelper::testSort("quickSortImproveRandom", quickSortImproveRandom, arrc3, n);

    delete (arr);  // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr2); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr3); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    return 0;
}