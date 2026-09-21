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

    //从后向前移动元素
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;    //写入新值
    list->size = list->size + 1;     //长度+1
    return 1;
}

// 练习 3：删除下标 index 处的元素，并通过指针参数 removed 把被删除的值传回调用者
// 成功返回 1，失败返回 0；失败情形：index 不在 [0, size - 1] 范围内
int removeAt(SeqList *list, int index, int *removed) {

    if (index < 0 || index >= list->size) {
        return 0;
    }
    //先保存被删除的值到*removed
    *removed = list->data[index];

    //被删后面的元素，从前向后逐个前移覆盖
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size = list->size - 1;   //长度-1
    return 1;
}

int main() {
    //1.初始化顺序表
    SeqList list;
    list.size = 4;
    list.data[0] = 10;
    list.data[1] = 20;
    list.data[2] = 30;
    list.data[3] = 40;
    printf("初始：");
    printList(&list);

    //2.调用insertAt()
    int ret = insertAt(&list,2,25);
    printf("insertAt(2, 25) 返回 %d\n", ret);
    printList(&list);

    //3.调用removeAt(&list, 1, &removed)
    int removed;
    ret = removeAt(&list,1,&removed);
    printf("removeAt(1) 返回 %d，删除的值是 %d\n", ret, removed);
    printList(&list);

    //4.调用 insertAt(&list, 10, 99)
    ret = insertAt(&list,10,99);
    printf("insertAt(10, 99) 返回 %d\n", ret);
    printList(&list);

    //5.调用 removeAt(&list, 4, &removed)
    ret = removeAt(&list,4,&removed);
    printf("removeAt(4) 返回 %d\n", ret);
    printList(&list);

    return 0;
}
// Created by Grape on 2026/9/12.
//
