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

    insertionSort(arr, n);
    bubbleSort(arr2, n);
    shellSort(arr3, n);

    SortTestHelper::testSort("shellSort", shellSort, arr3, n);
    SortTestHelper::testSort("bubbleSort", bubbleSort, arr2, n);
    SortTestHelper::testSort("insertionSort", insertionSort, arr, n);
    delete (arr); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr2); // 因为 arr2 开辟了一个数组空间，所以要在这里释放
    delete (arr3); // 因为 arr3 开辟了一个数组空间，所以要在这里释放
    return 0;
}