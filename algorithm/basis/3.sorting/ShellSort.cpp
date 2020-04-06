//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#include "ShellSort.h"
#include "../../tools.h"
#include <cmath>

int main() {
    int n = pow(2, 16);
    int *arr = Tools::generateRandomArray(n, 0, n);

    Tools::testSort("Shell sort", ShellSort::ascSort, arr, n);
    return 0;
}