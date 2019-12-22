#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2019/12/22
//
struct student {
    int no;
    char name[20];
    char addr[20];
    struct student *next;
};
typedef struct student LIST;

LIST *CreateList() {
    LIST *head = NULL, *prev, *cur;
    int i, n;
    head = NULL;
    printf("请输入节点个数:\n");
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        // 1. 动态生成一个节点，由指针cur指向该节点
        cur = (struct student *) malloc(sizeof(struct student));
        // 2. 因为当前节点一定是最后一个节点，所以将next指针域置为NULL
        cur->next = NULL;
        if (head == NULL) {
            head = cur;
        } else {
            // 3. 令指针prev的next域指向当前节点，使cur指向的节点成为链表中的最后一节点
            prev->next = cur;
        }
        printf("学号\t姓名\t地址\n");
        scanf("%d %s %s", &cur->no, cur->name, cur->addr);   /*为cur指向的节点输入数据*/
        prev = cur;
    }
    return head;
}

LIST *InsetNode(LIST *h, LIST *s) {
    LIST *pre, *p;
    p = h;
    if (h == NULL) {  /*如果链表为空*/
        h = s;          /* s 节点就是第一个节点，让头指针h 指向该节点 */
        s->next = NULL; /* 将s指向的节点的指针域z置为NULL */
    } else {
        /**
         * 如果链表不为空，则需要在链表中查找要插入的位置。在查找时，用到两个指针pre和p。
         * 其中，pre指向p指向的前一个节点。要插入的新节点位置应该为pre和p之间。查找插入位置的代码如下。
         */
        while ((s->no > p->no) && (p->next != NULL)) {
            pre = p;          /* pre指向p指向的节点的前面的一个节点 */
            p = p->next;      /* p指向下一个节点 */
        }
        if (s->no <= p->no) {
            if (h == p) {
                h = s;
                s->next = p;
            } else {
                pre->next = s;
                s->next = p;
            }
        } else {
            p->next = s;
            s->next = NULL;
        }
    }
    return h;
}

LIST *DeleteListNode(LIST *h, int no) {
    LIST *pre, *p;
    if (h == NULL) {
        printf("链表为空不能删除\n");
        return NULL;
    }
    p = h;
    while (p->no != no && p->next != NULL) {
        pre = p;
        p = pre->next;
    }
    if (p->no == no) {
        if (p == h) {
            h = p->next;
        } else {
            pre->next = p->next;
            free(p);
            printf("节点被成功删除.\n");
        }
    } else {
        printf("没有发现需要删除的节点\n");
        return h;
    }
    return h;
}

void DisplayList(LIST *head) {
    LIST *p = head;
    while (p != NULL) {
        printf("%d %s %s\n", p->no, p->name, p->addr);
        p = p->next;
    }
}

int main() {
    LIST *head, *p;
    int no;
    head = CreateList();
    printf("学号\t姓名\t地址\n");
    DisplayList(head);

    p = (LIST *) malloc(sizeof(LIST));
    printf("新插入节点\n");
    scanf("%d %s %s", &p->no, p->name, p->addr);   /*为cur指向的节点输入数据*/
    head = InsetNode(head, p);
    printf("学号\t姓名\t地址\n");
    DisplayList(head);
    printf("请输入一个要删除节点的学号:\n ");

    scanf("%d", &no);
    head = DeleteListNode(head, no);
    if (head == NULL) {
        printf("学号\t姓名\t地址\n");
        DisplayList(head);
    }
    DisplayList(head);
}