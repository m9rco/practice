//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/10
//

#include "tools.h"
#include "sort.h"
#include "basis/3.sorting/BubbleSort.h"
#include "basis/3.sorting/SelectionSort.h"
#include "basis/3.sorting/InsertionSort.h"
#include <cmath>


int main() {
    int n = pow(2, 16);
    int *ra0 = Tools::generateRandomArray(n, 0, n);
    int *ra1 = Tools::copyIntArray(ra0, n);
    int *ra2 = Tools::copyIntArray(ra0, n);

    cout << "\n === 2^16 random array === \n" << endl;
    // O(n^2)
    testSort("BubbleSort", BubbleSort::ascSort, ra0, n);
    testSort("SelectionSort", SelectionSort::ascSort, ra1, n);
    testSort("InsertionSort", InsertionSort::ascSort, ra2, n);
    testSort("InsertionSortImprove", InsertionSort::ascSortImprove, ra2, n);


    cout << "\n === nearly order array === \n" << endl;
    // nearly order
    int *oa0 = Tools::generateNearlyOrderedArray(n, n / 16);
    int *oa1 = Tools::copyIntArray(oa0, n);
    int *oa2 = Tools::copyIntArray(oa0, n);

    // O(n^2)
    testSort("BubbleSort", BubbleSort::ascSort, oa0, n);
    testSort("SelectionSort", SelectionSort::ascSort, oa1, n);
    testSort("InsertionSort", InsertionSort::ascSort, oa2, n);
    testSort("InsertionSortImprove", InsertionSort::ascSortImprove, oa2, n);
}