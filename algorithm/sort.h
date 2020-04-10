//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/10
//

#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H

#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
bool isSorted(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

template<typename T>
void testSort(const string &sortName, void (*sort)(T[], int), T arr[], int n) {
    clock_t startTime = clock();
    sort(arr, n);
    clock_t endTime = clock();
    assert(isSorted(arr, n));
    cout << sortName << " │ " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

#endif //ALGORITHM_SORT_H
