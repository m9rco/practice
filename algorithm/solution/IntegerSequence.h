//
// @author m9rco
// @date 2020/4/24
//

#ifndef ALGORITHM_INTEGERSEQUENCE_H
#define ALGORITHM_INTEGERSEQUENCE_H

#include <algorithm>
#include <iostream>

using namespace std;


namespace IntegerSequence {
    template<typename T>
    int findMinAbs(T arr[], int num) {
        if (num == 1) {
            return arr[0];
        }
        if (arr[0] >= 0) {
            return arr[0];
        }
        if (arr[num - 1] <= 0) {
            return arr[num - 1];
        }
        int target = 0, mid;
        int left = 0, right = num - 1;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return arr[mid];
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (abs(arr[left]) < abs(arr[right])) {
            return arr[left];
        }
        // 已排好序 无重复项的从小大大 O(nlog2n)
        return arr[right];
    }

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

        cout << mid << endl;
    }

    template<typename T>
    void ascSort(T *arr, int n) {
        __mergeSort(arr, 0, n - 1);
    }
};


#endif //ALGORITHM_INTEGERSEQUENCE_H
