//
// @author m9rco
// @date 2020/4/24
//

#include "IntegerSequence.h"


int main() {
    int arr[] = {-20, -1, 0, 1, 3};
    int carr[] = {1, 5, 2, 9, 8, 0, 6};

    cout << IntegerSequence::findMinAbs(arr, 5) << endl;

    IntegerSequence::ascSort(&carr, 7);
    return 0;
}