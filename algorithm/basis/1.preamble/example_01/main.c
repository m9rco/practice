#include <stdio.h>
//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2019/12/22
//

long factorial(int n);

int main() {
    for (int num = 0; num < 10; ++num) {
        printf("%d != %ld\n", num, factorial(num));
    }

}

long factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}