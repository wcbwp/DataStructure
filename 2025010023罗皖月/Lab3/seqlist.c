#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} SeqList;

// 练习 1：从下标 0 到 size - 1 依次输出所有有效元素，元素之间用一个空格分隔，末尾换行
void printList(const SeqList *list) {
    for (int i = 0; i < list->size; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", list->data[i]);
    }
    printf("\n");
}

// 练习 2：在下标 index 处插入 value，成功返回 1，失败返回 0
// 失败情形：顺序表已满（size == MAX_SIZE），或 index 不在 [0, size] 范围内
int insertAt(SeqList *list, int index, int value) {
    if (list->size == MAX_SIZE || index < 0 || index > list->size) {
        return 0;
    }
    // 从后向前移动，为 index 位置腾出空位
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->size++;
    return 1;
}

// 练习 3：删除下标 index 处的元素，并通过指针参数 removed 把被删除的值传回调用者
// 成功返回 1，失败返回 0；失败情形：index 不在 [0, size - 1] 范围内
int removeAt(SeqList *list, int index, int *removed) {
    if (removed == NULL || index < 0 || index >= list->size) {
        return 0;
    }
    *removed = list->data[index];
    // 从前向后移动，填补被删元素留下的空位
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