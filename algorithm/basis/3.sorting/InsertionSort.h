//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#ifndef ALGORITHM_INSERTIONSORT_H
#define ALGORITHM_INSERTIONSORT_H

#include <algorithm>

using namespace std;

namespace InsertionSort {
    template<typename T>
    void ascSort(T *arr, int n) {
        for (int i = 1; i < n; i++) {
            for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
                swap(arr[j], arr[j - 1]);
            }
        }
    }

    template<typename T>
    void ascSort(T arr[], int l, int r) {
        for (int i = l + 1; i <= r; i++) {
            T e = arr[i];
            int j;
            for (j = i; j > l && arr[j - 1] > e; j--)
                arr[j] = arr[j - 1];
            arr[j] = e;
        }
    }

    template<typename T>
    void ascSortImprove(T *arr, int n) {
        for (int i = 1; i < n; i++) {
            T e = arr[i];
            int j;
            for (j = i; j > 0 && e < arr[j - 1]; j--) {
                arr[j] = arr[j - 1];
            }
            arr[j] = e;
        }
    }
};


#endif //ALGORITHM_INSERTIONSORT_H
