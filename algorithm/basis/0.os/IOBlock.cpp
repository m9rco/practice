//
// @author m9rco
// @date 2020/4/21
//

#include "IOBlock.h"

int main() {

    /**
     *      gcc IOBlock.cpp -lstdc++
     *
            🤥 pushaowei🍭 14:46 ➜  0.os git:(master) ✗ ./a.out > out0
            1
            2
            3
            ^C
             ➜ 0.os git:(master) ✗ cat out0
            1
            2
            3
            🤥 pushaowei🍭 14:46 ➜  0.os git:(master) ✗ ./a.out < out0
            1
            2
            3
            🤥 pushaowei🍭 14:46 ➜  0.os git:(master) ✗ ./a.out < out0 > out1
            🤥 pushaowei🍭 14:47 ➜  0.os git:(master) ✗ cat out0
            1
            2
            3
            🤥 pushaowei🍭 14:47 ➜  0.os git:(master) ✗ cat out1
            1
            2
            3
     *
     */
    (IOBlock(4096)).terminal();
}