//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/10
//

#ifndef ALGORITHM__283_MOVEZEROES_H
#define ALGORITHM__283_MOVEZEROES_H

#include "vector"
#include "algorithm"
#include "iostream"

using namespace std;

class _283_MoveZeroes {
public:
    void moveZeroes(vector<int> &nums) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                if (k != i) {
                    swap(nums[k++], nums[i]);
                } else {
                    k++;
                }
            }
        }
    }
};

#endif //ALGORITHM__283_MOVEZEROES_H
