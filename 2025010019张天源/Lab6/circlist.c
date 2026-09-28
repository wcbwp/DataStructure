#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} CircList;

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

static Node* circLast(const CircList* list) {
    Node* p = list->head;
    while (p->next != list->head) {
        p = p->next;
    }
    return p;
}

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

int circEmpty(const CircList* list) {
    return list->head->next == list->head;
}

void circPrint(const CircList* list) {
    printf("[size = %d] ", list->size);
    for (Node* p = list->head->next; p != list->head; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

int circPushBack(CircList* list, int value) {
    insertAfter(circLast(list), value);
    list->size += 1;
    return 1;
}

int circInsert(CircList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) {
        return 0;
    }
    insertAfter(prevOf(list, rank), value);
    list->size += 1;
    return 1;
}

int circRemove(CircList* list, int rank, int* value) {
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    Node* p = unlinkAfter(list, prevOf(list, rank));
    *value = p->data;
    free(p);
    list->size -= 1;
    return 1;
}

int circFind(const CircList* list, int value) {
    int rank = 0;
    for (Node* p = list->head->next; p != list->head; p = p->next) {
        if (p->data == value) {
            return rank;
        }
        rank++;
    }
    return -1;
}

void circPrintAround(const CircList* list, int steps) {
    printf("walk %d steps around: ", steps);
    if (circEmpty(list)) {
        printf("(empty)");
    } else {
        Node* cur = list->head->next;
        for (int i = 0; i < steps; i++) {
            printf("%d ", cur->data);
            cur = cur->next;
            if (cur == list->head) {
                cur = cur->next;
            }
        }
    }
    printf("\n");
}

void circJosephus(CircList* list, int k) {
    printf("josephus n = %d, k = %d, out order: ", list->size, k);
    Node* prev = list->head;
    while (list->size > 0) {
        //走 k‑1 步，跳过哨兵
        for (int i = 0; i < k - 1; i++) {
            prev = prev->next;
            if (prev == list->head) {
                prev = prev->next;
            }
        }
        Node* out = unlinkAfter(list, prev);
        printf("%d ", out->data);
        free(out);
        list->size -= 1;
        //如果下一个是哨兵，跳到哨兵下一个
        if (prev->next == list->head) {
            prev = list->head;
        }
    }
    printf("\n");
}

int main(void) {
    CircList ring;
    circInit(&ring);
    printf("after init: ");
    circPrint(&ring);
    printf("circEmpty = %d\n\n", circEmpty(&ring));

    for (int i = 1; i <= 5; i++) {
        circPushBack(&ring, i);
    }
    printf("after circPushBack 1 to 5: ");
    circPrint(&ring);

    circPrintAround(&ring, 12);
    printf("\n");

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

    printf("circFind(4) = %d\n", circFind(&ring, 4));
    printf("circFind(99) = %d\n", circFind(&ring, 99));
    ok = circInsert(&ring, 6, 100);
    printf("circInsert(6, 100): ok = %d\n", ok);
    ok = circRemove(&ring, 5, &removed);
    printf("circRemove(5): ok = %d, removed = %d\n\n", ok, removed);

    circJosephus(&ring, 3);
    printf("after josephus: ");
    circPrint(&ring);
    printf("circEmpty = %d\n\n", circEmpty(&ring));

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

    printf("destroy by hand before main ends:\n");
    circDestroy(&ring3);
    circDestroy(&ring2);
    circDestroy(&ring);
    return 0;
}