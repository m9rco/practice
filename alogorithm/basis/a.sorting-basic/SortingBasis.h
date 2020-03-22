//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/15
//
#ifndef SORTBASIS_SORTINGBASIS_H
#define SORTBASIS_SORTINGBASIS_H

#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
void insertionSort(T *arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

template<typename T>
void insertionSort(T arr[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j - 1] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }

    return;
}


template<typename T>
void insertionSortImprove(T *arr, int n) {
    for (int i = 1; i < n; i++) {
        T e = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > e; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = e;
    }
}

template<typename T>
void shellSort(T *arr, int n) {
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


template<typename T>
void selectionSort(T *arr, int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;    // 寻找 [i, n] 区间里的最小值
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}


template<typename T>
void bubbleSort(T *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
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
}

template<typename T>
void mergeSort(T *arr, int n) {
    __mergeSort(arr, 0, n - 1);
}

template<typename T>
void mergeSortBottomUp(T *arr, int n) {
    for (int i = 1; i <= n; i += i) {
        for (int j = 0; j + i < n; j += i + i) {
            // arr[j...j+i-1] arr[j+i...j+2*i-1]
            __merge(arr, j, j + i - 1, min(j + i + i - 1, n - 1));
        }
    }
}

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
void __quickSortImproveInsertion(T *arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int p = __quickPartition(arr, left, right);

    __quickSortImproveInsertion(arr, left, p - 1);
    __quickSortImproveInsertion(arr, p + 1, right);
}

template<typename T>
void quickSort(T *arr, int n) {
    __quickSort(arr, 0, n - 1);
}

template<typename T>
void quickSortImproveInsertion(T *arr, int n) {
    __quickSortImproveInsertion(arr, 0, n - 1);
}



#endif //SORTBASIS_SORTINGBASIS_H
