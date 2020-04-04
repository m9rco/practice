//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2019/12/22
//

typedef struct {
    DataType list[ListSize];
    int length;
} SeqList;

int ListLength(SeqList L) {
    return L.length;
}

void ClearList(SeqList *L) {
    L->length = 0;
}

void InitList(SeqList *L) {
    L->length = 0;
}

int ListEmpty(SeqList L) {
    if (L.length == 0) {
        return 1;
    }
    return 0;
}

int GetElem(SeqList L, int i, DataType *e) {
    if (i < 1 || i > L.length) {
        return -1;
    }
    *e = L.list[i - 1];
    return 1;
}

int LocateElem(SeqList L, DataType e) {
    for (int i = 0; i < L.length; ++i) {
        if (L.list[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

int InsertList(SeqList *L, int i, DataType e) {
    int j;
    if (i < 1 || i > L->length + 1) {
        printf("插入位置%d不合法\n", i);
        return -1;
    } else if (L->length >= ListSize) {
        printf("顺序表已满，不能插入\n");
        return 0;
    } else {
        for (j = L->length; j >= i; j--) {
            L->list[j] = L->list[j - 1];
        }
        L->list[i - 1] = e;
        L->length = L->length + 1;
        return 1;
    }
}

int DeleteList(SeqList *L, int i, DataType *e) {
    int j;

    if (L->length <= 0) {
        printf("顺序表已空不能进行删除\n");
        return 0;
    } else if (i < 1 || i > L->length) {
        printf("删除位置不合适\n");
        return -1;
    } else {
        *e = L->list[i - 1];
        for (j = i; j <= L->length - 1; j++) {
            L->list[j - 1] = L->list[j];
        }
        L->length = L->length - 1;
        return 1;
    }
}


