#include <stdio.h>
//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2019/12/22
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void example_01() {
    int arr[] = {6, 7, 8, 9, 10};
    int *ptr;

    ptr = arr;
    *(ptr + 2) += 2;
    printf("%d,%d\n", *ptr, *(ptr + 2));
}

int main() {
    int n;
    printf("输入要执行的方法：\n");
    scanf("%d", &n);
    switch (n) {
        case 1:
            example_01();
            break;
    }

}

#pragma clang diagnostic pop