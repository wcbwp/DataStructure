#include <stdio.h>
#include <stdlib.h>

/* 结点：与课堂上写的完全相同，不得修改 */
typedef struct Node {
    int data;           /* 数据域：保存一个整数 */
    struct Node* next;  /* 指针域：保存下一个结点的地址，NULL 表示没有后继 */
} Node;

/* 链表：头哨兵的地址和有效结点个数打包在一起。
 * 与 Lab3 的 SeqList 一样，所有操作都通过 LinkedList* 参数访问它们 */
typedef struct {
    Node* head;         /* 头哨兵，data 不使用 */
    int size;           /* 有效结点个数，不含哨兵 */
} LinkedList;

static Node* newNode(int value) { ... }
static Node* insertAfter(Node* prev, int value) { ... }
static Node* unlinkAfter(Node* prev) { ... }
static Node* prevOf(const LinkedList* list, int rank) { ... }

/* 申请一个存放 value 的新结点。它的寿命不由作用域决定，而由 free 决定 */
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

/* 在 prev 后面插入一个存 value 的新结点，返回新结点。课堂上的两句 */
static Node* insertAfter(Node* prev, int value) {
    Node* p = newNode(value);
    p->next = prev->next;
    prev->next = p;
    return p;
}

/* 摘下 prev 后面的结点并返回它，只改指针，不释放 */
static Node* unlinkAfter(Node* prev) {
    Node* p = prev->next;
    if (p != NULL) {
        prev->next = p->next;
    }
    return p;
}

/* 秩为 rank 的结点的前驱；rank == 0 时是哨兵本身。从哨兵出发走 rank 步 */
static Node* prevOf(const LinkedList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
    }
    return p;
}

void listInit(LinkedList* list) { ... }
void listDestroy(LinkedList* list) { ... }
int listSize(const LinkedList* list) { ... }
int listEmpty(const LinkedList* list) { ... }                                                 

/* 建立空表：立哨兵。对应课堂上 main 开头的 head = newNode(0) */
void listInit(LinkedList* list) {
    list->head = newNode(0);
    list->size = 0;
}

/* 释放整条链，哨兵也在链上。末尾的输出是验证手段，原样保留 */
void listDestroy(LinkedList* list) {
    int count = 0;
    Node* p = list->head;
    while (p != NULL) {
        Node* next = p->next;   /* 先记住下一个，再 free 当前这个 */
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

/* 练习 1：输出。从第一个有效结点开始输出，哨兵不输出，每个数后面一个空格，末尾换行 */
void listPrint(const LinkedList* list) {
    printf("[size = %d] ", list->size);
    for (const Node* p = list->head->next; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

/* 练习 2：在秩 rank 处插入 value，合法范围 0 <= rank <= size
 * 成功返回 1 并让 size 加一；rank 非法返回 0，链表不变 */
int listInsert(LinkedList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) return 0;
    insertAfter(prevOf(list, rank), value);
    list->size++;
    return 1;
}

/* 练习 3：顺序追加与表头插入，都复用 listInsert，不得另写接链代码 */
int listPushBack(LinkedList* list, int value) {
    return listInsert(list, list->size, value);
}

int listPushFront(LinkedList* list, int value) {
    return listInsert(list, 0, value);
}

/* 练习 4：删除秩 rank 处的结点，被删的值写入 *value，合法范围 0 <= rank < size
 * 成功返回 1 并让 size 减一；失败返回 0 且不修改 *value
 * 必须用局部变量 p 接住 unlinkAfter 的返回值，并单独一行写 free(p);（3.5 的断点设在这一行） */
int listRemove(LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) return 0;
    Node* p = unlinkAfter(prevOf(list, rank));
    *value = p->data;
    free(p);
    list->size--;
    return 1;
}

/* 练习 5：按秩读取，合法范围 0 <= rank < size；失败时不修改 *value */
int listGet(const LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) return 0;
    *value = prevOf(list, rank)->next->data;
    return 1;
}

/* 练习 6：按值查找，返回第一次出现的秩，找不到返回 -1。从 head->next 开始数，秩从 0 起 */
int listFind(const LinkedList* list, int value) {
    int rank = 0;
    for (const Node* p = list->head->next; p != NULL; p = p->next, rank++) {
        if (p->data == value) return rank;
    }
    return -1;
}

// ---- main 原样放在最后 ----
int main(void) { ... }
