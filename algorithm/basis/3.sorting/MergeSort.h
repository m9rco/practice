//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#ifndef ALGORITHM_MERGESORT_H
#define ALGORITHM_MERGESORT_H

#include <algorithm>
#include <cmath>

using namespace std;


namespace MergeSort {

    template<typename T>
    void __merge(T *arr, int l, int mid, int r) {
        T aux[r - l + 1];
        for (int i = l; i <= r; i++) {
            aux[i - l] = arr[i];
        }
        int i = l, j = mid + 1;
        for (int k = l; k <= r; k++) {
            if (i > mid) {
                arr[k] = aux[j - l];
                j++;
            } else if (j > r) {
                arr[k] = aux[i - l];
                i++;
            } else if (aux[i - l] < aux[j - l]) {
                arr[k] = aux[i - l];
                i++;
            } else {
                arr[k] = aux[j - l];
                j++;
            }
        }
    }

    template<typename T>
    void __mergeSort(T *arr, int l, int r) {
        if (l >= r) {
            return;
        }
        int mid = (int) (l + r) / 2;
        __mergeSort(arr, l, mid);
        __mergeSort(arr, mid + 1, r);
        __merge(arr, l, mid, r);
    }

    template<typename T>
    void ascSort(T *arr, int n) {
        __mergeSort(arr, 0, n - 1);
    }

    template<typename T>
    void ascSortBottomUp(T *arr, int n) {
        for (int i = 1; i <= n; i += i) {
            for (int j = 0; j + i < n; j += i + i) {
                // arr[j...j+i-1] arr[j+i...j+2*i-1]
                __merge(arr, j, j + i - 1, min(j + i + i - 1, n - 1));
            }
        }
    }
};


#endif //ALGORITHM_MERGESORT_H
