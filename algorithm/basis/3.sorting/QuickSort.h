//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/6
//

#ifndef ALGORITHM_QUICKSORT_H
#define ALGORITHM_QUICKSORT_H

#include <algorithm>
#include <cmath>
#include "InsertionSort.h"

using namespace std;

namespace QuickSort {
    template<typename T>
    int __quickPartition(T *arr, int left, int right) {
        T index = arr[left];
        int j = left;
        for (int i = left + 1; i <= right; i++) {
            if (arr[i] < index) {
                j++;
                swap(arr[j], arr[i]);
            }
        }
        swap(arr[left], arr[j]);
        return j;
    }

    template<typename T>
    void __quickSort(T *arr, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = __quickPartition(arr, left, right);

        __quickSort(arr, left, p - 1);
        __quickSort(arr, p + 1, right);
    }

    template<typename T>
    void ascSort(T *arr, int n) {
        __quickSort(arr, 0, n - 1);
    }

    template<typename T>
    void __quickSortImprove3way(T *arr, int left, int right) {
        if (right - left <= 15) {
            InsertionSort::ascSort(arr, left, right);
            return;
        }
        swap(arr[left], arr[rand() % (right - left + 1) + left]);
        T v = arr[left];

        int lt = left;          // arr[left+1 ... lt] < v
        int gt = right + 1;     // arr[gt ... rt] > v
        int i = left + 1;       // arr[lt+1 ... i] == v

        while (i < gt) {
            if (arr[i] < v) {
                swap(arr[i], arr[lt + 1]);
                lt++;
                i++;
            } else if (arr[i] > v) {
                swap(arr[i], arr[gt - 1]);
                gt--;
            } else { // arr[i] == v
                i++;
            }
        }
        swap(arr[left], arr[lt]);
        __quickSortImprove3way(arr, left, lt - 1);
        __quickSortImprove3way(arr, gt, right);
    }

    template<typename T>
    void ascSortImprove3way(T *arr, int n) {
        srand((unsigned) time(nullptr)); // NOLINT(cert-msc51-cpp)
        __quickSortImprove3way(arr, 0, n - 1);
    }

    template<typename T>
    void __quickSortImproveInsertion(T *arr, int left, int right) {
        if (right - left <= 15) {
            InsertionSort::ascSort(arr, left, right);
            return;
        }
        int p = __quickPartition(arr, left, right);

        __quickSortImproveInsertion(arr, left, p - 1);
        __quickSortImproveInsertion(arr, p + 1, right);
    }


    template<typename T>
    void ascSortImproveInsertion(T *arr, int n) {
        __quickSortImproveInsertion(arr, 0, n - 1);
    }

    template<typename T>
    int __quickRandomPartition(T *arr, int left, int right) {
        swap(arr[left], arr[rand() % (right - left + 1) + left]);
        T index = arr[left];
        int j = left;
        for (int i = left + 1; i <= right; i++) {
            if (arr[i] < index) {
                j++;
                swap(arr[j], arr[i]);
            }
        }
        swap(arr[left], arr[j]);
        return j;
    }


    template<typename T>
    void __quickSortImproveRandom(T *arr, int left, int right) {
        if (right - left <= 15) {
            InsertionSort::ascSort(arr, left, right);
            return;
        }
        srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
        int p = __quickRandomPartition(arr, left, right);

        __quickSortImproveRandom(arr, left, p - 1);
        __quickSortImproveRandom(arr, p + 1, right);
    }

    template<typename T>
    void ascSortImproveRandom(T *arr, int n) {
        __quickSortImproveRandom(arr, 0, n - 1);
    }


    template<typename T>
    int __quickSortImproveRandomV2Partition(T *arr, int left, int right) {
        swap(arr[left], arr[rand() % (right - left + 1) + left]);
        T index = arr[left];
        int i = left + 1, j = right;

        // arr[left+1..i] <= index; arr[j...right] >= index
        while (true) {
            while (i <= right && arr[i] < index) {
                i++;       //
            }
            while (j >= left + 1 && arr[j] > index) {
                j--;
            }
            if (i > j) {
                break;
            }
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
        swap(arr[left], arr[j]);
        return j;
    }

    template<typename T>
    void __quickSortImproveRandomV2(T *arr, int left, int right) {
        if (right - left <= 15) {
            InsertionSort::ascSort(arr, left, right);
            return;
        }
        srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
        int p = __quickSortImproveRandomV2Partition(arr, left, right);

        __quickSortImproveRandomV2(arr, left, p - 1);
        __quickSortImproveRandomV2(arr, p + 1, right);
    }

    template<typename T>
    void ascSortImproveRandomV2(T *arr, int n) {
        __quickSortImproveRandomV2(arr, 0, n - 1);
    }
};


#endif //ALGORITHM_QUICKSORT_H
