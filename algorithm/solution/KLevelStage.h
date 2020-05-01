//
// @author m9rco
// @date 2020/4/24
//

#ifndef ALGORITHM_KLEVELSTAGE_H
#define ALGORITHM_KLEVELSTAGE_H

#include <algorithm>
#include <iostream>

using namespace std;

namespace KLevelStage {

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

};


#endif //ALGORITHM_KLEVELSTAGE_H
