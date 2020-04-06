//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#include "QuickSort.h"
#include "../../tools.h"
#include <cmath>

int main() {
    int n = pow(2, 16);
    int *arr = Tools::generateRandomArray(n, 0, n);
    int *arr2 = Tools::copyIntArray(arr, n);
    int *arr3 = Tools::copyIntArray(arr, n);
    int *arr4 = Tools::copyIntArray(arr, n);
    int *arr5 = Tools::copyIntArray(arr, n);

    Tools::testSort("Quick sort", QuickSort::ascSort, arr, n);
    Tools::testSort("Quick sort improve 3way", QuickSort::ascSortImprove3way, arr2, n);
    Tools::testSort("Quick sort improve insertion", QuickSort::ascSortImproveInsertion, arr3, n);
    Tools::testSort("Quick sort improve random", QuickSort::ascSortImproveRandom, arr4, n);
    Tools::testSort("Quick sort improve v2", QuickSort::ascSortImproveRandomV2, arr5, n);
    return 0;
}