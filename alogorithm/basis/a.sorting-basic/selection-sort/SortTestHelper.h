//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/1
//

#ifndef BASIS_SORTTESTHELPER_H
#define BASIS_SORTTESTHELPER_H

#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

namespace SortTestHelper {
    int *generateRandomArray(int n, int rangeL, int rangeR) {
        assert(rangeL <= rangeR);
        int *arr = new int[n];
        srand((unsigned) time(nullptr));
        for (int i = 0; i < n; ++i) {
            arr[i] = (int) random() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    template<typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    template<typename T>
    bool isSorted(T arr[], int n) {
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    void testSort(const string& sortName, void(*sort)(T[], int), T arr[], int n) {
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();
        assert(isSorted(arr, n));

        cout << sortName << ":\t" << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    }

}
#endif //BASIS_SORTTESTHELPER_H
