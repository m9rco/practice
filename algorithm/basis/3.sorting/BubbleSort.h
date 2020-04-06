//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#ifndef ALGORITHM_BUBBLE_H
#define ALGORITHM_BUBBLE_H

#include <algorithm>

using namespace std;

namespace BubbleSort {

    template<typename T>
    void ascSort(T *arr, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};


#endif //ALGORITHM_BUBBLE_H
