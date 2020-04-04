//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2019/12/22
//
#define ListSize 100

#include <stdio.h>

typedef int DataType;

#include "SeqList.h"

void UnionAB(SeqList *A, SeqList B);

int main() {
    int i, flag;
    DataType e;
    DataType a[] = {2, 3, 17, 20, 9, 31};
    DataType b[] = {8, 31, 5, 17, 22, 9, 48, 67};
    SeqList LA, LB;
    InitList(&LA);
    InitList(&LB);

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        if (InsertList(&LA, i + 1, a[i]) == 0) {
            printf("位置不合法 LA");
            return 0;
        }
    }
    for (i = 0; i < sizeof(b) / sizeof(b[0]); i++) {
        if (InsertList(&LB, i + 1, b[i]) == 0) {
            printf("位置不合法 LB");
            return 0;
        }
    }
    printf("顺序表LA中的元素:\n");
    for (i = 0; i <= LA.length; i++) {
        flag = GetElem(LA, i, &e);
        if (flag == 1) {
            printf("%4d", e);
        }
    }
    printf("\n");
    printf("顺序表LB中的元素：\n");
    for (i = 0; i <= LB.length; i++) {
        flag = GetElem(LB, i, &e);
        if (flag == 1) {
            printf("%4d", e);
        }
    }
    printf("\n");
    printf("将LB中但不在LA中但元素插入到LA中：\n");
    UnionAB(&LA, LB);
    for (i = 0; i < LA.length; ++i) {
        flag = GetElem(LA, i, &e);
        if (flag == 1) {
            printf("%4d", e);
        }
    }
    printf("\n");
}

void UnionAB(SeqList *LA, SeqList LB) {
    int i, flag, pos;
    DataType e;
    for (i = 0; i < LB.length; ++i) {
        flag = GetElem(LB, i, &e);
        if (flag == 1) {
            pos = LocateElem(*LA, e);
            if (!pos) {
                InsertList(LA, LA->length + 1, e);
            }
        }
    }
}