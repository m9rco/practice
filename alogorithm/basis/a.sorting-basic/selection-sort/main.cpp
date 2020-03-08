// 选择排序
//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/1
//

#include "SortTestHelper.h"
#include "algorithm"

using namespace std;

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

int main() {
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    selectionSort(arr, n);
    SortTestHelper::printArray(arr, n);
    SortTestHelper::testSort("selectionSort", selectionSort, arr, n);
    delete (arr); // 因为 arr 开辟了一个数组空间，所以要在这里释放
    return 0;
}