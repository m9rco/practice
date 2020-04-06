//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#include "SelectionSort.h"
#include "../../tools.h"
#include <cmath>

int main() {
    int n = pow(2, 16);
    int *arr = Tools::generateRandomArray(n, 0, n);

    Tools::testSort("Selection sort", SelectionSort::ascSort, arr, n);
    return 0;
}