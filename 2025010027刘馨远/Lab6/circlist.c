#include <stdio.h>
#include <stdlib.h>

// ==================== 基础结点定义 ====================
typedef struct Node {
    int data;               // 数据域
    struct Node* next;      // 指针域，指向下一个结点
} Node;

// ==================== 链表结构体定义 ====================
typedef struct {
    Node* head;             // 头哨兵
    int size;               // 有效结点个数
} LinkedList;

typedef struct {
    Node* head;             // 头哨兵
    int size;               // 有效结点个数
} CircList;

// ==================== 基础工具函数 ====================
// 创建一个新结点 (2.2节，从堆malloc，用完必须free)
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

// ==================== 单链表 LinkedList 实现 ====================
// 初始化单链表 (2.3节)
void listInit(LinkedList* list) {
    list->head = newNode(0); // 头哨兵不存有效数据
    list->head->next = NULL;
    list->size = 0;
}

// 释放整条单链表
void listDestroy(LinkedList* list) {
    Node* p = list->head;
    while (p != NULL) {
        Node* next = p->next;
        free(p);
        p = next;
    }
    list->head = NULL;
    list->size = 0;
}

// 找秩为 rank 的前驱 (2.5节)
static Node* prevOf(LinkedList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
    }
    return p;
}

// 插入 (2.4节，插入两句)
int listInsert(LinkedList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) return 0; // 范围 0 到 size

    Node* prev = prevOf(list, rank);
    Node* p = newNode(value);

    p->next = prev->next; // 先接后
    prev->next = p;       // 再断前
    list->size++;
    return 1;
}

// 删除 (2.4节，删除一句)
int listRemove(LinkedList* list, int rank, int* removed) {
    if (rank < 0 || rank >= list->size) return 0; // 范围 0 到 size - 1

    Node* prev = prevOf(list, rank);
    Node* p = prev->next; // 要删除的结点

    *removed = p->data;   // 先保存值
    prev->next = p->next; // 断链
    free(p);              // 释放内存
    list->size--;
    return 1;
}

// 按秩读取
int listGet(LinkedList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) return 0;
    *value = prevOf(list, rank)->next->data;
    return 1;
}

// 打印
void listPrint(LinkedList* list) {
    Node* p = list->head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ==================== 循环单链表 CircList 实现 ====================
// 初始化循环单链表 (2.6节)
void circInit(CircList* list) {
    list->head = newNode(0);
    list->head->next = list->head; // 空表：哨兵指向自己
    list->size = 0;
}

// 释放循环单链表
void circDestroy(CircList* list) {
    Node* p = list->head->next;
    while (p != list->head) {
        Node* next = p->next;
        free(p);
        p = next;
    }
    free(list->head);
    list->size = 0;
}

// 循环链表按秩插入
int circInsert(CircList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) return 0;

    Node* prev = list->head;
    for (int i = 0; i < rank; i++) prev = prev->next;

    Node* p = newNode(value);
    p->next = prev->next;
    prev->next = p;
    list->size++;
    return 1;
}

// 循环链表打印
void circPrint(CircList* list) {
    Node* p = list->head->next;
    while (p != list->head) { // 停止条件改为 != head
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ==================== 约瑟夫环问题 (2.7节) ====================
void josephus(CircList* list, int k) {
    Node* prev = list->head; // 始终是“下一个报1的结点”的前驱

    printf("出列顺序: ");

    while (list->size > 0) {
        // 2. 让 prev 向前走 k-1 步，如果下一个是哨兵就跳过哨兵
        for (int i = 0; i < k - 1; i++) {
            if (prev->next == list->head) {
                prev = list->head;
            }
            prev = prev->next;
        }

        // 3. 此时 prev 后面的结点就是要报到 k 的人
        if (prev->next == list->head) {
            prev = list->head; // 确保 prev 不是指向哨兵
        }
        Node* toRemove = prev->next;

        printf("%d ", toRemove->data);

        // 4. 摘下并 free
        prev->next = toRemove->next;
        if (prev->next == list->head) {
            prev = list->head; // 如果下一个是哨兵，让 prev = head
        }
        free(toRemove);
        list->size--;
    }
    printf("\n");
}

// ==================== 测试主函数 ====================
int main() {
    // 测试单链表
    printf("===== 单链表测试 =====\n");
    LinkedList list;
    listInit(&list);
    listInsert(&list, 0, 10);
    listInsert(&list, 1, 20);
    listInsert(&list, 2, 30);
    listInsert(&list, 3, 40);
    printf("初始: ");
    listPrint(&list);

    listInsert(&list, 2, 25);
    printf("insert(2, 25) 后: ");
    listPrint(&list);

    int removed;
    listRemove(&list, 1, &removed);
    printf("remove(1) 后: ");
    listPrint(&list);
    printf("删除的值是: %d\n", removed);

    listDestroy(&list);

    // 测试约瑟夫环
    printf("\n===== 约瑟夫环测试 n=6, k=2 =====\n");
    CircList clist;
    circInit(&clist);
    for (int i = 1; i <= 6; i++) {
        circInsert(&clist, clist.size, i); // 尾插法构建 1 2 3 4 5 6
    }
    printf("初始循环链表: ");
    circPrint(&clist);

    josephus(&clist, 2); // 应输出 2 4 6 3 1 5

    return 0;
}//
// Created by 17413 on 2026/9/23.
//
