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

    selectionSort(arr2, n);
    insertionSort(arr, n);

    SortTestHelper::testSort("selectionSort", selectionSort, arr2, n);
    SortTestHelper::testSort("insertionSort", insertionSort, arr, n);
    delete (arr); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    delete (arr2); // 因为 arr2 开辟了一个数组空间，所以要在这里释放
    return 0;
}



