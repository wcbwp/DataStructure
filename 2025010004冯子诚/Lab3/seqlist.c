#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} SeqList;

void printList(const SeqList *list) {
    printf("初始: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int insertAt(SeqList *list, int index, int value) {
    // 判断是否已满或下标是否合法
    if (list->size == MAX_SIZE || index < 0 || index > list->size) {
        return 0;
    }
    // 从最后一个有效元素开始，从后向前逐个后移
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->size++;
    return 1;
}

int removeAt(SeqList *list, int index, int *removed) {
    // 判断下标是否合法
    if (index < 0 || index >= list->size) {
        return 0;
    }
    // 保存被删除的值
    *removed = list->data[index];
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

    // 1. 输出初始内容
    printList(&list);

    // 2. 调用 insertAt
    int ret = insertAt(&list, 2, 25);
    printf("insertAt(2, 25) 返回 %d\n", ret);
    printList(&list);

    // 3. 调用 removeAt
    int removed;
    ret = removeAt(&list, 1, &removed);
    printf("removeAt(1) 返回 %d, 删除的值是 %d\n", ret, removed);
    printList(&list);

    // 4. 调用 insertAt 下标不合法
    ret = insertAt(&list, 10, 99);
    printf("insertAt(10, 99) 返回 %d\n", ret);
    printList(&list);

    // 5. 调用 removeAt 下标不合法
    ret = removeAt(&list, 4, &removed);
    printf("removeAt(4) 返回 %d\n", ret);
    printList(&list);

    return 0;
}