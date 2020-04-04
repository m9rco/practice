//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/3/29
//

#include "main.h"
#include <iostream>

using namespace std;


int main() {
    HeapMax<int> maxHeap = HeapMax<int>(7);
    srand(time(nullptr));

    for (int i = 0; i < 7; i++) {
        maxHeap.insert(rand() % 100);
    }
    maxHeap.testPrint();
    return 0;
}