#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} SeqList;

// 练习 1：遍历输出
void printList(const SeqList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d", list->data[i]);
        if (i != list->size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

// 练习 2：在下标 index 处插入 value
int insertAt(SeqList *list, int index, int value) {
    if (list->size == MAX_SIZE) {
        return 0;                       // 已满
    }
    if (index < 0 || index > list->size) {
        return 0;                       // 下标不合法
    }
    // 从最后一个有效元素开始，从后向前后移
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->size++;
    return 1;
}

// 练习 3：删除下标 index 处的元素
int removeAt(SeqList *list, int index, int *removed) {
    if (index < 0 || index >= list->size) {
        return 0;                       // 下标不合法
    }
    if (removed != NULL) {
        *removed = list->data[index];   // 先保存被删的值
    }
    // 从前向后逐个前移
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
    return 1;
}

int main() {
    SeqList list;
    list.size = 4;
    list.data[0] = 10;
    list.data[1] = 20;
    list.data[2] = 30;
    list.data[3] = 40;

    printf("初始: ");
    printList(&list);

    int r = insertAt(&list, 2, 25);
    printf("insertAt(2, 25) 返回 %d\n", r);
    printList(&list);

    int removed;
    r = removeAt(&list, 1, &removed);
    printf("removeAt(1) 返回 %d, 删除的值是 %d\n", r, removed);
    printList(&list);

    r = insertAt(&list, 10, 99);
    printf("insertAt(10, 99) 返回 %d\n", r);
    printList(&list);

    r = removeAt(&list, 4, &removed);
    printf("removeAt(4) 返回 %d\n", r);
    printList(&list);

    return 0;
}