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
    selectionSort(arr, n);
    SortTestHelper::printArray(arr, n);
    SortTestHelper::testSort("selectionSort", selectionSort, arr, n);
    delete (arr); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    return 0;
}