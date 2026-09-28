#include <stdio.h>
#include <stdlib.h>

/* 结点与单链表完全相同 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* 循环链表的约定：最后一个结点的 next 指回 head；空表时 head->next == head */
typedef struct {
    Node* head;
    int size;
} CircList;

/* --------------------------------------------------------------------------
 * 教师提供：结点级操作，与 linkedlist.c 对照
 * -------------------------------------------------------------------------- */

static Node* newNode(int value) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        printf("malloc failed, exit\n");
        exit(1);
    }
    p->data = value;
    p->next = NULL;
    return p;
}

static Node* insertAfter(Node* prev, int value) {
    Node* p = newNode(value);
    p->next = prev->next;
    prev->next = p;
    return p;
}

static Node* unlinkAfter(const CircList* list, Node* prev) {
    Node* p = prev->next;
    if (p == list->head) {
        return NULL;
    }
    prev->next = p->next;
    return p;
}

static Node* prevOf(const CircList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
    }
    return p;
}

/* 练习 1：最后一个有效结点 */
static Node* circLast(const CircList* list) {
    Node* p = list->head;
    while (p->next != list->head) {
        p = p->next;
    }
    return p;
}

/* --------------------------------------------------------------------------
 * 教师提供：建立与销毁
 * -------------------------------------------------------------------------- */

void circInit(CircList* list) {
    list->head = newNode(0);
    list->head->next = list->head;
    list->size = 0;
}

void circDestroy(CircList* list) {
    int count = 0;
    while (list->size > 0) {
        Node* p = unlinkAfter(list, list->head);
        free(p);
        list->size--;
        count++;
    }
    free(list->head);
    list->head = NULL;
    printf("(circDestroy: freed %d nodes, including the sentinel)\n", count + 1);
}

int circSize(const CircList* list) {
    return list->size;
}

/* --------------------------------------------------------------------------
 * 学生练习
 * -------------------------------------------------------------------------- */

/* 练习 2：空表判断，用指针关系 */
int circEmpty(const CircList* list) {
    return list->head->next == list->head;
}

/* 练习 3：遍历 */
void circPrint(const CircList* list) {
    printf("[size = %d] ", list->size);
    for (Node* p = list->head->next; p != list->head; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

/* 练习 4：追加到表尾 */
int circPushBack(CircList* list, int value) {
    insertAfter(circLast(list), value);
    list->size++;
    return 1;
}

/* 练习 5：按秩插入 */
int circInsert(CircList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) {
        return 0;
    }
    insertAfter(prevOf(list, rank), value);
    list->size++;
    return 1;
}

/* 练习 6：按秩删除 */
int circRemove(CircList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    Node* p = unlinkAfter(list, prevOf(list, rank));
    if (value != NULL) {
        *value = p->data;
    }
    free(p);
    list->size--;
    return 1;
}

/* 练习 7：按值查找 */
int circFind(const CircList* list, int value) {
    Node* p = list->head->next;
    int rank = 0;
    while (p != list->head) {
        if (p->data == value) {
            return rank;
        }
        p = p->next;
        rank++;
    }
    return -1;
}

/* 练习 8：绕圈走 steps 步 */
void circPrintAround(const CircList* list, int steps) {
    printf("walk %d steps around: ", steps);
    if (circEmpty(list)) {
        printf("(empty)");
    } else {
        Node* p = list->head->next;
        for (int i = 0; i < steps; i++) {
            if (p == list->head) {
                p = p->next;
                continue;
            }
            printf("%d ", p->data);
            p = p->next;
        }
    }
    printf("\n");
}

/* 练习 9：约瑟夫问题 */
void circJosephus(CircList* list, int k) {
    printf("josephus n = %d, k = %d, out order: ", list->size, k);

    Node* prev = list->head;

    while (list->size > 0) {
        /* 报数：从 prev 的下一个开始，走 k-1 步，落在要出列结点的前驱 */
        for (int i = 0; i < k - 1; i++) {
            prev = prev->next;
            if (prev == list->head) {
                prev = prev->next;
            }
        }

        /* 出列：prev 后面就是要出列的结点 */
        Node* out = unlinkAfter(list, prev);
        printf("%d ", out->data);
        free(out);
        list->size--;

        /* 下一轮报 1 从出列结点的下一个开始，prev 不变（它已经是新起点的前驱） */
        /* 但如果 prev 恰好是哨兵，需要再跳一步 */
        if (prev->next == list->head && list->size > 0) {
            prev = prev->next;
        }
    }

    printf("\n");
}

/* --------------------------------------------------------------------------
 * 统一 main 函数
 * -------------------------------------------------------------------------- */

int main(void) {
    CircList ring;
    circInit(&ring);
    printf("after init: ");
    circPrint(&ring);
    printf("circEmpty = %d\n\n", circEmpty(&ring));

    /* 1. 依次追加 1 到 5 */
    for (int i = 1; i <= 5; i++) {
        circPushBack(&ring, i);
    }
    printf("after circPushBack 1 to 5: ");
    circPrint(&ring);

    /* 2. 绕圈走 12 步 */
    circPrintAround(&ring, 12);
    printf("\n");

    /* 3. 中间插入、删除，再删除表尾并追加 */
    int ok = circInsert(&ring, 2, 25);
    printf("circInsert(2, 25): ok = %d, ", ok);
    circPrint(&ring);
    int removed = 777;
    ok = circRemove(&ring, 2, &removed);
    printf("circRemove(2): ok = %d, removed = %d, ", ok, removed);
    circPrint(&ring);
    ok = circRemove(&ring, 4, &removed);
    printf("circRemove(4): ok = %d, removed = %d, ", ok, removed);
    circPrint(&ring);
    ok = circPushBack(&ring, 5);
    printf("circPushBack(5): ok = %d, ", ok);
    circPrint(&ring);
    circPrintAround(&ring, 7);
    printf("\n");

    /* 4. 查找与非法位置 */
    printf("circFind(4) = %d\n", circFind(&ring, 4));
    printf("circFind(99) = %d\n", circFind(&ring, 99));
    ok = circInsert(&ring, 6, 100);
    printf("circInsert(6, 100): ok = %d\n", ok);
    ok = circRemove(&ring, 5, &removed);
    printf("circRemove(5): ok = %d, removed = %d\n\n", ok, removed);

    /* 5. 约瑟夫问题 n = 5, k = 3 */
    circJosephus(&ring, 3);
    printf("after josephus: ");
    circPrint(&ring);
    printf("circEmpty = %d\n\n", circEmpty(&ring));

    /* 6. 再来两组 */
    CircList ring2;
    circInit(&ring2);
    for (int i = 1; i <= 7; i++) {
        circPushBack(&ring2, i);
    }
    circJosephus(&ring2, 2);

    CircList ring3;
    circInit(&ring3);
    circPushBack(&ring3, 1);
    circJosephus(&ring3, 1);

    /* 7. 收尾 */
    printf("destroy by hand before main ends:\n");
    circDestroy(&ring3);
    circDestroy(&ring2);
    circDestroy(&ring);
    return 0;
}