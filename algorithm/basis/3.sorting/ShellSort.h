//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#ifndef ALGORITHM_SHELLSORT_H
#define ALGORITHM_SHELLSORT_H

#include <algorithm>
#include <cmath>

using namespace std;

namespace ShellSort {
    template<typename T>
    void ascSort(T *arr, int n) {
        int gap = 1;
        while (gap < n / 3) {
            gap = gap * 3 + 1;
        }
        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                int j;
                T e = arr[i];
                for (j = i; j >= gap && e < arr[j - gap]; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = e;
            }
            gap = (int) floor(gap / 3);
        }
    }
};


#endif //ALGORITHM_SHELLSORT_H
