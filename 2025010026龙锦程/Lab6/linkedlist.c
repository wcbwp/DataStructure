#include <stdio.h>
#include <stdlib.h>

/* 结点：与课堂上写的完全相同，不得修改 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* 链表：头哨兵的地址和有效结点个数打包在一起 */
typedef struct {
    Node* head;
    int size;
} LinkedList;

/* --------------------------------------------------------------------------
 * 教师提供：结点级操作，不得修改
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

static Node* unlinkAfter(Node* prev) {
    Node* p = prev->next;
    if (p != NULL) {
        prev->next = p->next;
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

/* --------------------------------------------------------------------------
 * 教师提供：建立与销毁
 * -------------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------------
 * 学生练习
 * -------------------------------------------------------------------------- */

/* 练习 1：输出 */
void listPrint(const LinkedList* list) {
    printf("[size = %d] ", list->size);
    for (const Node* p = list->head->next; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

/* 练习 2：在秩 rank 处插入 value */
int listInsert(LinkedList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) {
        return 0;
    }

    insertAfter(prevOf(list, rank), value);
    list->size++;
    return 1;
}

/* 练习 3：顺序追加与表头插入 */
int listPushBack(LinkedList* list, int value) {
    return listInsert(list, list->size, value);
}

int listPushFront(LinkedList* list, int value) {
    return listInsert(list, 0, value);
}

/* 练习 4：删除秩 rank 处的结点 */
int listRemove(LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) {
        return 0;
    }

    Node* p = unlinkAfter(prevOf(list, rank));

    if (value != NULL) {
        *value = p->data;
    }

    free(p);
    list->size--;
    return 1;
}

/* 练习 5：按秩读取 */
int listGet(const LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) {
        return 0;
    }

    Node* p = prevOf(list, rank)->next;

    if (value != NULL) {
        *value = p->data;
    }

    return 1;
}

/* 练习 6：按值查找 */
int listFind(const LinkedList* list, int value) {
    const Node* p = list->head->next;
    int rank = 0;

    while (p != NULL) {
        if (p->data == value) {
            return rank;
        }
        p = p->next;
        rank++;
    }

    return -1;
}

/* --------------------------------------------------------------------------
 * 统一 main 函数
 * -------------------------------------------------------------------------- */

int main(void) {
    LinkedList list;
    listInit(&list);
    printf("after init: ");
    listPrint(&list);
    printf("listEmpty = %d, listSize = %d\n\n", listEmpty(&list), listSize(&list));

    /* 1. 依次追加五个样例元素 */
    int samples[] = {18, -1, 42, 18, 65};
    for (int i = 0; i < 5; i++) {
        listPushBack(&list, samples[i]);
    }
    printf("after listPushBack 18, -1, 42, 18, 65: ");
    listPrint(&list);
    printf("\n");

    /* 2. 在秩 2 处插入 25 */
    int ok = listInsert(&list, 2, 25);
    printf("listInsert(2, 25): ok = %d, ", ok);
    listPrint(&list);

    /* 3. 删除秩 1 处的元素，并输出被删除的值 */
    int removed = 777;
    ok = listRemove(&list, 1, &removed);
    printf("listRemove(1): ok = %d, removed = %d, ", ok, removed);
    listPrint(&list);

    /* 4. 在表头插入 7 */
    ok = listPushFront(&list, 7);
    printf("listPushFront(7): ok = %d, ", ok);
    listPrint(&list);
    printf("\n");

    /* 5. 按秩读取：合法的秩与越界的秩 */
    int value = 777;
    ok = listGet(&list, 0, &value);
    printf("listGet(0): ok = %d, value = %d\n", ok, value);
    value = 777;
    ok = listGet(&list, 6, &value);
    printf("listGet(6): ok = %d, value = %d\n\n", ok, value);

    /* 6. 按值查找：重复元素只返回第一次出现的秩 */
    printf("listFind(42) = %d\n", listFind(&list, 42));
    printf("listFind(18) = %d\n", listFind(&list, 18));
    printf("listFind(99) = %d\n\n", listFind(&list, 99));

    /* 7. 非法位置：负秩、超过 size 的秩、删除空表 */
    ok = listInsert(&list, -1, 100);
    printf("listInsert(-1, 100): ok = %d\n", ok);
    ok = listInsert(&list, 100, 100);
    printf("listInsert(100, 100): ok = %d\n", ok);

    LinkedList empty;
    listInit(&empty);
    ok = listRemove(&empty, 0, &removed);
    printf("empty listRemove(0): ok = %d\n\n", ok);

    /* 8. 收尾 */
    printf("before destroy: ");
    listPrint(&list);
    printf("destroy by hand before main ends, empty first, then list:\n");
    listDestroy(&empty);
    listDestroy(&list);
    return 0;
}