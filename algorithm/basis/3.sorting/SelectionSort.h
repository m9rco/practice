//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#ifndef ALGORITHM_SELECTIONSORT_H
#define ALGORITHM_SELECTIONSORT_H

#include <algorithm>


using namespace std;

namespace SelectionSort {

    template<typename T>
    void ascSort(T *arr, int n) {
        for (int i = 0; i < n; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            swap(arr[i], arr[min]);
        }
    }

};


#endif //ALGORITHM_SELECTIONSORT_H
