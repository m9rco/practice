//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#include "InsertionSort.h"
#include "../../tools.h"
#include <cmath>

int main() {
    int n = pow(2, 16);
    int *arr = Tools::generateRandomArray(n, 0, n);
    int *arr2 = Tools::copyIntArray(arr, n);

    Tools::testSort("Insertion Sort", InsertionSort::ascSort, arr, n);
    Tools::testSort("Insertion Sort Improve", InsertionSort::ascSortImprove, arr2, n);

    delete[] arr;
    delete[] arr2;
    return 0;
}