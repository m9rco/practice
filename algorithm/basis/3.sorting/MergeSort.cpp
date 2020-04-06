//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#include "MergeSort.h"

#include "../../tools.h"
#include <cmath>

int main() {
    int n = pow(2, 16);
    int *arr = Tools::generateRandomArray(n, 0, n);
    int *arr2 = Tools::copyIntArray(arr, n);

    Tools::testSort("MergeSort asc sort", MergeSort::ascSort, arr, n);
    Tools::testSort("MergeSort asc sort bottom up", MergeSort::ascSortBottomUp, arr2, n);
    return 0;
}