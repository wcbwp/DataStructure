#include <stdio.h>
#include <stdlib.h>

/* 结点：与课堂上写的完全相同，不得修改 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* 链表：头哨兵的地址和有效结点个数打包在一起。 */
typedef struct {
    Node* head;
    int size;
} LinkedList;

/* ----------------------------------------------------
 * 教师提供：结点级操作，课堂代码原样搬来，不得修改
 * ---------------------------------------------------- */

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

static Node* unlinkAfter(Node* prev) {
    Node* p = prev->next;
    if (p != NULL) {
        prev->next = p->next;
        p->next = NULL;
    }
    return p;
}

static Node* prevOf(const LinkedList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
    }
    return p;
}

/* ----------------------------------------------------
 * 教师提供：建立与销毁
 * ---------------------------------------------------- */

void listInit(LinkedList* list) {
    list->head = newNode(0);
    list->size = 0;
}

void listDestroy(LinkedList* list) {
    int count = 0;
    Node* p = list->head;
    while (p != NULL) {
        Node* next = p->next;
        free(p);
        p = next;
        count++;
    }
    list->head = NULL;
    list->size = 0;
    printf("(listDestroy: freed %d nodes, including the sentinel)\n", count);
}

int listSize(const LinkedList* list) {
    return list->size;
}

int listEmpty(const LinkedList* list) {
    return list->size == 0;
}

/* ----------------------------------------------------
 * 学生练习
 * ---------------------------------------------------- */

void listPrint(const LinkedList* list) {
    printf("[size = %d] ", list->size);
    for (const Node* p = list->head->next; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

int listInsert(LinkedList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) {
        return 0;
    }
    insertAfter(prevOf(list, rank), value);
    list->size++;
    return 1;
}

int listPushBack(LinkedList* list, int value) {
    return listInsert(list, list->size, value);
}

int listPushFront(LinkedList* list, int value) {
    return listInsert(list, 0, value);
}

int listRemove(LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    Node* p = unlinkAfter(prevOf(list, rank));
    *value = p->data;
    free(p);
    list->size--;
    return 1;
}

int listGet(const LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    *value = prevOf(list, rank)->next->data;
    return 1;
}

int listFind(const LinkedList* list, int value) {
    int rank = 0;
    for (const Node* p = list->head->next; p != NULL; p = p->next) {
        if (p->data == value) {
            return rank;
        }
        rank++;
    }
    return -1;
}

/* ----------------------------------------------------
 * 主函数：全英文输出（彻底消除乱码）
 * ---------------------------------------------------- */

int main(void) {
    LinkedList list;
    listInit(&list);

    printf("after init: [size = %d]\n", listSize(&list));
    printf("listEmpty = %d, listSize = %d\n", listEmpty(&list), listSize(&list));

    printf("\nafter listPushBack 18, -1, 42, 18, 65:\n");
    listPushBack(&list, 18);
    listPushBack(&list, -1);
    listPushBack(&list, 42);
    listPushBack(&list, 18);
    listPushBack(&list, 65);
    listPrint(&list);

    int ok = listInsert(&list, 2, 25);
    printf("listInsert(2, 25): ok = %d, ", ok);
    listPrint(&list);

    int removed;
    printf("listRemove(1): ok = %d, removed = %d, ", listRemove(&list, 1, &removed), removed);
    listPrint(&list);

    printf("listPushFront(7): ok = %d, ", listPushFront(&list, 7));
    listPrint(&list);

    int value;
    printf("\nlistGet(0): ok = %d, value = %d\n", listGet(&list, 0, &value), value);
    value = 777;
    printf("listGet(6): ok = %d, value = %d\n", listGet(&list, 6, &value), value);

    printf("\nlistFind(42) = %d\n", listFind(&list, 42));
    printf("listFind(18) = %d\n", listFind(&list, 18));
    printf("listFind(99) = %d\n", listFind(&list, 99));

    printf("\nlistInsert(-1, 100): ok = %d\n", listInsert(&list, -1, 100));
    printf("listInsert(100, 100): ok = %d\n", listInsert(&list, 100, 100));
    printf("empty listRemove(0): ok = %d\n", listRemove(&list, 0, &removed));

    printf("\nbefore destroy: ");
    listPrint(&list);
    printf("destroy by hand before main ends, empty first, then list:\n");
    listDestroy(&list);

    return 0;
}