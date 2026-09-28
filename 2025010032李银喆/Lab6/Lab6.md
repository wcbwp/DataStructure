# Lab6：用 C 实现带头哨兵的单链表与循环单链表

> **作业目标**：把课堂上从四个具名结点一路走到的"带头哨兵的 C 链表"补完整：结点从 `malloc` 来，`head` 与 `size` 打包进一个 `LinkedList` 结构体，按秩完成输出、顺序追加、中间插入、删除、按秩读取和按值查找；在同一套结点上做出**循环单链表**，用它解约瑟夫问题；用 CLion 断点、单步和 Memory View 亲眼看到"插入只改指针、删除先断链后释放"。
>
> 本说明给出了新增知识、两个程序的框架、统一测试和期望输出。两个程序各自是一个单独的 `.c` 文件，全部用 C 语言完成。课堂上已经写过的 `newNode`、`insertAfter`、`unlinkAfter` 以及建立、销毁函数由教师提供，学生补的是按秩操作和与"圈"有关的函数。本次不涉及 C++，不涉及 `class`、`new/delete`、构造函数和析构函数，这些放在 Lab7。
>
> **检查说明**：程序和书面题沿用前几次作业的完成度检查口径，内容正确性将在期末统一检测。本次要交三张截图，图片审核会检查是否展示真实的 CLion 调试界面，以及指定时刻的变量、地址和内存数据是否对应。空文件、未作答模板、占位程序和缺失截图不属于完成；自动审核规则以课程仓库发布的 Lab6 配置为准。

---

## 一、配置 CMakeLists.txt

保留 Lab5，在新的 `Lab6` 目录中完成本次作业。两个程序各有一个 `main`，所以要写两个目标，在 CLion 右上角切换运行。

```cmake
cmake_minimum_required(VERSION 3.20)
project(Lab6 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab6_list linkedlist.c)
add_executable(lab6_circ circlist.c)
```

要求：

- 有且只有两个 `add_executable`，目标名与源文件名与上面完全一致。
- `project(...)` 与前几次作业一致，同时声明 `C` 和 `CXX`。本次两个源文件都是 `.c`，按 C11 编译。
- 保存后重新加载 CMake 项目。两个目标互相独立，一个没写完不影响另一个编译。
- 本次仍然需要提交 `CMakeLists.txt`。

---

## 二、完成本次作业所需的新知识

### 2.1 结点：`next` 里存的是地址

```c
typedef struct Node {
    int data;           /* 数据域：保存一个整数 */
    struct Node* next;  /* 指针域：保存下一个结点的地址，NULL 表示没有后继 */
} Node;
```

- 结构体还在定义之中，里面就出现了指向自己的指针 `struct Node* next`。这是允许的，因为指针长度固定；写成 `struct Node next` 会编译错误。
- `p->data` 等价于 `(*p).data`：`p` 是指向结点的指针用 `->`，结点变量本身用 `.`。
- `sizeof(Node)` 是 16 而不是 12：`int` 占 4 字节，指针占 8 字节，编译器为对齐补了 4 字节。3.5 的 Memory View 会亲眼看到这 16 个字节。

### 2.2 结点从 `malloc` 来，用完必须 `free`

```c
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
```

- 栈上的结点活不过 `return`，所以插入函数里的新结点只能从堆上申请，寿命由 `free` 决定，不由作用域决定。
- 每摘下一个结点都要问一句：它当初是怎么来的，该不该 `free`。本次所有结点都是 `malloc` 来的，摘下之后必须 `free`，否则就是内存泄漏。
- `free(p)` 之后不能再读 `p->data` 或 `p->next`。释放整条链时要**先记住下一个，再 `free` 当前这个**。

### 2.3 头哨兵与 `LinkedList` 结构体

```c
typedef struct {
    Node* head;         /* 头哨兵，data 不使用 */
    int size;           /* 有效结点个数，不含哨兵 */
} LinkedList;
```

- **头哨兵**是一个不存有效数据、永远占着表头位置的结点。有了它，"第一个有效结点的前驱"总是存在，表头插入和删除就不需要单独处理。有效数据从 `head->next` 开始，遍历时不要从 `head` 开始，否则会多打一个 0。
- 课堂上的 `head` 是 `main` 里的局部变量。本次把它和 `size` 打包进 `LinkedList`，所有函数通过 `LinkedList*` 参数访问它们，这和 Lab3 把 `data` 与 `size` 打包进 `SeqList` 是同一件事。
- `size` 必须单独记录：链表不像向量那样能用"首地址加秩"算出有效范围。`listInsert` 成功后 `size` 加一，`listRemove` 成功后减一，忘了任何一处 `listPrint` 里的计数就对不上。
- `LinkedList list;` 只是一个局部变量，里面还没有任何结点，必须先 `listInit(&list)`。用完必须 `listDestroy(&list)`，C 语言没有析构函数，释放要自己写在 `main` 里。

### 2.4 插入两句与删除一句

```c
/* 在 prev 后面插入 p：先让新结点接住后面，再让前面接住新结点。顺序不能反 */
p->next = prev->next;
prev->next = p;

/* 摘掉 prev 后面的结点：只改前驱的一根指针 */
prev->next = prev->next->next;
```

插入和删除各自只改指针，没有一个 `data` 被移动过。写反插入两句会让新结点指向自己，后半条链再也走不到。删除之后必须 `free` 被摘下的结点；`free` 之前必须先断链，否则链上会留下一个指向已释放内存的指针。

### 2.5 按秩操作：从前驱出发

链表没有下标，秩为 `rank` 的结点只能从哨兵出发走 `rank` 步才能到。本次两个程序里都有一个私有的定位函数 `prevOf`，学生不用写，但要看懂：

| 调用 | 返回什么 | `rank` 的范围 |
| :--- | :--- | :--- |
| `prevOf(list, rank)` | 秩为 `rank` 的结点的**前驱**；`rank == 0` 时是哨兵 | `0 <= rank <= size` |

单链表要拿前驱，是因为插入和删除改的都是前驱的 `next`。`prevOf(list, size)` 返回最后一个有效结点，正好是追加时需要的前驱。

按秩操作的合法范围与 Lab4 的向量完全一致：`listInsert` 允许 `rank == size`（追加到末尾），`listRemove` 和 `listGet` 不允许。

### 2.6 循环单链表：最后一个结点指回哨兵

```text
单链表：  head → [1] → [2] → [3] → NULL
循环链表：head → [1] → [2] → [3] ┐
          ↑____________________┘
```

只改一个约定：最后一个结点的 `next` 不再是 `NULL`，而是指回 `head`。由此带来三处变化，写循环链表时每一处都要过一遍脑子：

| 单链表 | 循环链表 |
| :--- | :--- |
| 空表：`head->next == NULL` | 空表：`head->next == head`，哨兵指向自己 |
| 遍历停止条件：`p != NULL` | 遍历停止条件：`p != head`。写成 `p != NULL` 会**死循环** |
| 找最后一个结点：`p->next == NULL` | 找最后一个结点：`p->next == head` |

插入两句和删除一句**一字不差**，只是 `unlinkAfter` 判断边界时从"后面是不是 `NULL`"改成"后面是不是 `head`"。好处是从任何一个结点出发都能走遍整条链，这正是约瑟夫问题需要的。**哨兵也在圈上**，绕圈报数时走到哨兵要跳过它。

### 2.7 约瑟夫问题

`n` 个人围成一圈，从第一个人开始报数，报到 `k` 的人出列，从他的下一个人重新从 1 报起，直到所有人出列。用循环链表做：

1. 维护一个指针 `prev`，它始终是"下一个报 1 的结点"的**前驱**，初始为 `head`。
2. 让 `prev` 向前走 `k - 1` 步，走的过程中如果下一个是哨兵就跳过哨兵。
3. 此时 `prev` 后面那个结点就是报到 `k` 的人，用 `unlinkAfter` 摘下、输出、`free`。
4. 摘下之后 `prev->next` 自动变成出列者的下一个人，正好是下一轮报 1 的人；如果它是哨兵，让 `prev = head`。
5. 重复直到 `size == 0`。

手工模拟 `n = 5, k = 3`：`1 2 3 4 5` → 出 3，剩 `1 2 4 5` 从 4 报起 → 出 1，剩 `2 4 5` 从 2 报起 → 出 5，剩 `2 4` 从 2 报起 → 出 2 → 出 4。出列顺序 `3 1 5 2 4`。

为什么维护"前驱"而不是"当前正在报数的人"：出列的动作是摘链，摘链改的是前驱的 `next`。手里握着前驱，摘一个结点只要一句；握着当前结点，单链表上回头找前驱是走不通的。

### 2.8 本次不要求

不要求 C++、类、`new/delete`、构造函数、析构函数、模板、头文件拆分、尾指针、排序或有序插入。C++ 版本的 `IntList` 类和双向链表放在 Lab7。

---

## 三、linkedlist.c：补完课堂上的带头哨兵单链表

### 3.1 必须使用的框架

下面的框架可以直接编译运行（输出全是错的），把每一处 `TODO` 换成正确实现即可。不得修改结点与 `LinkedList` 的定义，不得修改函数的名字、参数、返回类型和参数里的 `const`，不得修改教师提供的函数。

（框架代码见 linkedlist.c）

### 3.2 实现要求

1. `Node`、`LinkedList` 的定义和四个 `static` 工具函数不得修改；`listInit`、`listDestroy`、`listSize`、`listEmpty` 原样保留。
2. `listInsert()` 必须复用 `insertAfter(prevOf(list, rank), value)`，不得另写一套接链代码；成功后 `size` 加一。
3. `listRemove()` 必须复用 `unlinkAfter(prevOf(list, rank))`，用局部变量 `Node* p` 接住返回值，取出 `data` 之后**单独一行**写 `free(p);`，然后 `size` 减一。3.5 的断点要设在这一行。
4. `listGet()` 与 `listFind()` 只读，参数里的 `const` 不得删除；`listGet()` 失败时不修改 `*value`。`*value` 是 C 语言的指针输出参数，用法与 Lab3 的 `removeAt` 相同，写入前要先判空。
5. `listFind()` 的秩从第一个有效结点算起为 0，哨兵不计入；重复元素返回第一次出现的秩。
6. `listPushBack()`、`listPushFront()` 必须复用 `listInsert`，它们是本次的检查点之一。
7. 只能包含 `<stdio.h>` 和 `<stdlib.h>`；不得使用 C++ 的 `iostream`、`cout`、`bool`、`new`、`delete`，不得使用数组代替链表，不得使用全局变量。
8. `listDestroy` 末尾那行输出是教师提供的验证手段，原样保留，不得在其他函数里增加调试输出。

### 3.3 统一 main 函数

把下面代码**原样**放在所有函数之后。

（main 代码见 linkedlist.c）

### 3.4 期望输出与核对重点

```text
after init: [size = 0] 
listEmpty = 1, listSize = 0

after listPushBack 18, -1, 42, 18, 65: [size = 5] 18 -1 42 18 65 

listInsert(2, 25): ok = 1, [size = 6] 18 -1 25 42 18 65 
listRemove(1): ok = 1, removed = -1, [size = 5] 18 25 42 18 65 
listPushFront(7): ok = 1, [size = 6] 7 18 25 42 18 65 

listGet(0): ok = 1, value = 7
listGet(6): ok = 0, value = 777

listFind(42) = 3
listFind(18) = 1
listFind(99) = -1

listInsert(-1, 100): ok = 0
listInsert(100, 100): ok = 0
empty listRemove(0): ok = 0

before destroy: [size = 6] 7 18 25 42 18 65 
destroy by hand before main ends, empty first, then list:
(listDestroy: freed 1 nodes, including the sentinel)
(listDestroy: freed 7 nodes, including the sentinel)
```

### 3.5 必做：CLion 断点、单步与 Memory View 截图

#### 3.5.1 准备调试

1. CMake 配置选择 **Debug**，运行目标选择 `lab6_list`，重新构建后用 **Debug** 启动。
2. 在 `main` 中 `int ok = listInsert(&list, 2, 25);` 这一行设第一个断点，运行到这里停下。此时五个样例已经追加完，`listInsert(2, 25)` 还没执行。
3. **停在第一个断点之后**，再在 `insertAfter` 里的 `prev->next = p;` 这一行设第二个断点，在 `listRemove` 里的 `free(p);` 这一行设第三个断点。
4. 三张图必须来自**同一次 Debug 运行**。

#### 3.5.2 三张截图的固定位置

**A．新结点已接住后面、前驱还没改：`imgs/insert_before_link.png`**

**B．前驱改完之后：`imgs/insert_after_link.png`**

**C．已断链、尚未释放：`imgs/remove_before_free.png`**

#### 3.5.3 怎样读结点的 16 个字节

`sizeof(Node)` 是 16：`int data` 占 4 字节，编译器为对齐补 4 字节，`Node* next` 占 8 字节。在 Memory View 里把每行字节数调成 16，一个结点正好一行：

| 位置 | 字节数 | 内容 |
| :--- | :---: | :--- |
| 第 0～3 字节 | 4 | `data`，小端序：25 是 `19 00 00 00`，-1 是 `ff ff ff ff`，42 是 `2a 00 00 00` |
| 第 4～7 字节 | 4 | 对齐填充，内容不定，不要去读 |
| 第 8～15 字节 | 8 | `next` 的地址，小端序 |

#### 3.5.4 必填：调试观察记录

| 记录项目 | 图 A：前驱还没改 | 图 B：前驱改完 | 图 C：已断链、尚未释放 |
| :--- | :--- | :--- | :--- |
| `p` 的地址 | 0x0000000000b316f0 | 0x0000000000b316f0 | 0x0000000000b315f0 |
| `p->data` | 25 | 25 | -1 |
| `p->next` 的地址 | 0x0000000000b31630 | 0x0000000000b31630 | 0x0000000000b31630 |
| `prev->next` 的地址（图 C 填 `list->head->next`） | 0x0000000000b31630 | 0x0000000000b316f0 | 0x0000000000b316f0 |
| `list->size` | 5 | 5 | 5 |

回答下面两个问题：

1. 图 A 到图 B 之间，`p` 这个结点的 16 个字节有没有变化？`prev` 这个结点的 16 个字节里哪几个变了？

> 图 A 到图 B 之间，`p` 这个结点的 16 个字节没有变化，因为 `p` 是新申请的结点，它的 `data` 和 `next` 在 `newNode` 时就已经确定了。`prev` 这个结点的 16 个字节中，只有第 8～15 字节（`next` 指针域）发生了变化，从原来指向 42 所在结点的地址（0x0000000000b31630）变成了指向 `p` 的地址（0x0000000000b316f0）。前 4 字节的 `data` 和中间 4 字节的对齐填充都没有改变。

2. 图 C 里 `p` 的 `next` 还指着 25 所在的结点，为什么这不会导致 25 被重复释放？如果把 `listRemove` 里的 `free(p);` 删掉，程序输出会不会变？会少掉什么？

> `p` 被摘下后，虽然它的 `next` 仍然指向 25 所在的结点（0x0000000000b31630），但链表上已经没有任何指针指向 `p` 了（`list->head->next` 已经绕过了 `p`，直接指向了 0x0000000000b316f0），所以 `p` 成了一个孤立的结点，释放它不会影响链表上其他结点。25 所在的结点仍然被链表上的其他指针引用着，不会被重复释放。如果把 `listRemove` 里的 `free(p);` 删掉，程序的输出不会改变（因为 `free` 不产生输出），但会造成内存泄漏——被摘下的结点占用的内存永远不会被回收。最后 `listDestroy` 打印的释放节点数会少 1，从 `freed 7 nodes` 变成 `freed 6 nodes`。

---

## 四、circlist.c：循环单链表与约瑟夫问题

### 4.1 必须使用的框架

（框架代码见 circlist.c）

### 4.2 实现要求

1. `circLast()` 从 `head` 出发循环，停止条件用 `p->next != list->head`，空表时返回 `head` 本身。
2. `circEmpty()` 必须用指针关系判断，不许写 `return list->size == 0`。
3. `circPushBack()` 复用 `insertAfter(circLast(list), value)`，`size` 加一。它是 `O(n)` 的，书面题会问为什么。
4. `circInsert()`、`circRemove()` 分别复用 `insertAfter(prevOf(...), value)` 与 `unlinkAfter(list, prevOf(...))`，写法与 `linkedlist.c` 对照；出列或删除的结点必须 `free`。
5. `circPrintAround(steps)` 走的步数可以超过 `size`；每走到哨兵就跳到哨兵的下一个，哨兵本身不输出。空表时只输出 `(empty)`。
6. `circJosephus(k)` 按 2.7 的五步实现，出列的结点必须 `free`，出列一个 `size` 减一；结束时表为空，哨兵仍在。不得先把数据拷进数组再模拟。
7. 遍历条件一律用 `!= list->head`，不得出现 `!= NULL`。
8. 只能包含 `<stdio.h>` 和 `<stdlib.h>`；不得使用数组、C++ 语法或全局变量。

### 4.3 统一 main 函数

（main 代码见 circlist.c）

### 4.4 期望输出与核对重点

```text
after init: [size = 0] 
circEmpty = 1

after circPushBack 1 to 5: [size = 5] 1 2 3 4 5 
walk 12 steps around: 1 2 3 4 5 1 2 3 4 5 1 2 

circInsert(2, 25): ok = 1, [size = 6] 1 2 25 3 4 5 
circRemove(2): ok = 1, removed = 25, [size = 5] 1 2 3 4 5 
circRemove(4): ok = 1, removed = 5, [size = 4] 1 2 3 4 
circPushBack(5): ok = 1, [size = 5] 1 2 3 4 5 
walk 7 steps around: 1 2 3 4 5 1 2 

circFind(4) = 3
circFind(99) = -1
circInsert(6, 100): ok = 0
circRemove(5): ok = 0, removed = 5

josephus n = 5, k = 3, out order: 3 1 5 2 4 
after josephus: [size = 0] 
circEmpty = 1

josephus n = 7, k = 2, out order: 2 4 6 1 5 3 7 
josephus n = 1, k = 1, out order: 1 
destroy by hand before main ends:
(circDestroy: freed 1 nodes, including the sentinel)
(circDestroy: freed 1 nodes, including the sentinel)
(circDestroy: freed 1 nodes, including the sentinel)
```

---

## 五、选择题与填空

### 5.1 插入的顺序

在 `prev` 后面插入新结点 `p`，正确的两句顺序是：

- [ ] A. `prev->next = p; p->next = prev->next;`
- [x] B. `p->next = prev->next; prev->next = p;`
- [ ] C. 两句顺序无所谓，结果一样
- [ ] D. `p->next = prev; prev->next = p;`

### 5.2 写反了会怎样

如果把 5.1 的两句写反，执行之后：

- [ ] A. 编译错误
- [ ] B. 新结点插不进去，链表不变
- [x] C. 新结点的 `next` 指向它自己，原来 `prev` 后面的结点再也走不到
- [ ] D. 新结点插到了表头

### 5.3 为什么先断链后释放

`listRemove` 必须先 `unlinkAfter` 再 `free`，原因是：

- [x] A. `free` 之后 `p->next` 不能再读，前驱就接不上后面了
- [ ] B. 先 `free` 会导致编译错误
- [ ] C. 顺序无所谓，只要两件事都做
- [ ] D. `unlinkAfter` 内部会自动 `free`

### 5.4 释放整条链

`listDestroy` 释放整条链的循环体，正确的写法是：

- [ ] A. `free(p); p = p->next;`
- [x] B. `Node* next = p->next; free(p); p = next;`
- [ ] C. 只写一句 `free(list->head);`，后面的结点会跟着一起释放
- [ ] D. 不用释放，`main` 结束时局部变量自动消失

### 5.5 头哨兵

带头哨兵的单链表，空表的判断条件是：

- [ ] A. `head == NULL`
- [x] B. `head->next == NULL`
- [ ] C. `head->data == 0`
- [ ] D. `size == -1`

### 5.6 为什么 `size` 要单独记录

`LinkedList` 里除了 `head` 还要有一个 `size` 成员，原因是：

- [ ] A. C 语言的结构体至少要有两个成员
- [x] B. 链表无法像向量那样用"首地址加秩"算出有效范围，元素个数要么单独维护，要么每次从头数一遍
- [ ] C. `malloc` 需要知道 `size` 才能申请结点
- [ ] D. 没有 `size` 就无法遍历链表

### 5.7 按秩访问的代价

对带头哨兵的单链表，`listGet(list, rank, &value)` 的时间复杂度是：

- [ ] A. `O(1)`，和向量一样
- [x] B. `O(rank)`，最坏 `O(n)`，因为要从哨兵走 `rank` 步
- [ ] C. `O(log n)`
- [ ] D. `O(n²)`

### 5.8 "链表插入是 O(1)"的前提

下列哪种说法是对的：

- [ ] A. 链表在任何位置插入都是 `O(1)`
- [x] B. 已经拿到前驱结点的地址时，接链是 `O(1)`；按秩找到前驱本身是 `O(n)`
- [ ] C. 只有在表头插入是 `O(1)`，其他位置都是 `O(n²)`
- [ ] D. 链表插入是 `O(1)`，因为不用申请内存

### 5.9 结点的字节

`sizeof(Node)` 是 16 而不是 12，原因是：

- [ ] A. `int` 占 8 个字节
- [ ] B. 指针占 4 个字节，`int` 占 12 个字节
- [x] C. `int` 占 4 字节、指针占 8 字节，编译器为让指针对齐到 8 字节边界补了 4 个字节
- [ ] D. `struct` 关键字占 4 个字节

### 5.10 循环链表的空表

带头哨兵的循环单链表，空表的判断条件是：

- [ ] A. `head->next == NULL`
- [ ] B. `head == NULL`
- [x] C. `head->next == head`，哨兵指向自己
- [ ] D. `head->next->next == head`

### 5.11 循环链表的遍历

对循环单链表写 `for (Node* p = list->head->next; p != NULL; p = p->next)`，结果是：

- [ ] A. 正常输出全部元素
- [ ] B. 只输出第一个元素
- [x] C. 死循环，因为链上没有任何一个 `next` 是 `NULL`
- [ ] D. 编译错误

### 5.12 循环链表的表尾追加

本次 `circPushBack` 的复杂度是 `O(n)`，如果给 `CircList` 加一个 `Node* tail` 成员，`circPushBack` 会变成：

- [ ] A. 仍是 `O(n)`，因为还要遍历一遍检查
- [x] B. `O(1)`，直接 `insertAfter(tail, value)` 再更新 `tail`
- [ ] C. `O(log n)`
- [ ] D. 无法实现，循环链表没有"尾"

### 5.13 填空：程序运行验证

两个程序的实际运行输出是否与 3.4、4.4 的期望输出完全一致？

- [x] A. 两个都一致
- [ ] B. 有不一致

如果选择"有不一致"，请说明哪个程序、哪一行不同以及原因：

> 无

### 5.14 填空：手工模拟约瑟夫

不运行程序，手工模拟 `n = 6, k = 2`（六个人编号 1 到 6，从 1 开始报数，报到 2 的出列），把每一轮的状态填进表里：

| 轮次 | 出列前的圈（从下一个报 1 的人开始写） | 出列者 |
| :---: | :--- | :---: |
| 1 | `1 2 3 4 5 6` | 2 |
| 2 | `3 4 5 6 1` | 4 |
| 3 | `5 6 1 3` | 6 |
| 4 | `1 3 5` | 1 |
| 5 | `3 5` | 3 |
| 6 | `5` | 5 |

最终出列顺序：2 4 6 1 3 5

### 5.15 填空：单链表与循环单链表的对照

把右列补全，至少填写四行：

| 项目 | 单链表 `LinkedList` | 循环单链表 `CircList` |
| :--- | :--- | :--- |
| 空表条件 | `head->next == NULL` | `head->next == head` |
| 遍历停止条件 | `p != NULL` | `p != head` |
| 最后一个结点的特征 | `p->next == NULL` | `p->next == head` |
| `unlinkAfter` 里"后面没有结点"的判断 | `p == NULL` | `p == head` |
| 表尾追加复杂度 | `O(n)` | `O(n)`（无尾指针时） |
| 从最后一个结点再走一步到哪里 | 无处可走（`NULL`） | 回到头哨兵（`head`） |

### 5.16 填空：向量与链表

用三到五句话回答：本次 `listPushBack` 是 `O(n)`，Lab5 的 `IntVector::pushBack` 是均摊 `O(1)`；但 `listInsert(list, 0, v)` 是 `O(1)`，`IntVector` 在下标 0 处插入是 `O(n)`。两者各自"快"在哪一步、"慢"在哪一步？什么场合该选链表？

> 链表的 `listPushBack` 是 `O(n)`，因为没有尾指针时需要从头遍历到最后一个结点才能追加，"慢"在找尾部这一步。向量的 `pushBack` 是均摊 `O(1)`，因为尾部追加只需在数组末尾写入，但当容量不足时需要重新分配并复制全部元素，分摊下来均摊为 `O(1)`。反过来，链表的 `listInsert(list, 0, v)` 是 `O(1)`，因为只需改两根指针就能在表头插入，不需要移动任何元素；而向量在下标 0 处插入是 `O(n)`，因为要把后面所有元素依次后移一位。当需要频繁在中间或头部插入删除时应选链表（如实现队列、频繁插入的场景）；当需要频繁按下标随机访问或在尾部追加时应选向量（如实现栈、需要缓存友好的遍历场景）。

---

## 六、提交要求

将本文件复制到自己的 `学号姓名/Lab6/Lab6.md`，填写选择题答案、填空和 3.5.4 的观察记录。最终只提交以下 **7 个文件，其中包含三张必交截图**：

```text
学号姓名/
└── Lab6/
    ├── CMakeLists.txt
    ├── linkedlist.c
    ├── circlist.c
    ├── Lab6.md
    └── imgs/
        ├── insert_before_link.png
        ├── insert_after_link.png
        └── remove_before_free.png
```

特别注意：

- `CMakeLists.txt` 必须包含 `lab6_list`、`lab6_circ` 两个目标，源文件分别为 `linkedlist.c`、`circlist.c`。
- 两个 `.c` 都必须是能独立编译运行的完整 C 程序，包含框架里的全部函数和本文给出的原样 `main`，不能只提交增量片段。
- `Lab6.md` 必须保留题目结构，填写选择题答案、填空和 3.5.4 的观察记录；3.5.2 中三处 Markdown 图片引用必须原样保留，不得删除或改写路径。
- 每道单项选择题必须且只能将一个 `[ ]` 改为 `[x]`，包括 5.13 的运行验证。
- 填写内容不能留空：5.13 选择"两个都一致"时填写"无"；5.14 六轮和最终顺序全部填写；5.15 至少四行；5.16 填写解释；3.5.4 的表格和两个问题填写完整。
- 三张截图必须满足 3.5 的状态、界面和地址关系要求，文件名与上面的目录树一致，并能在 `Lab6.md` 的 3.5.2 对应位置正常显示；不另交普通运行结果截图。
- 程序和书面题的完成度检查不代替正确性验证；截图会按 3.5 的要求检查。
- 不要提交整个 CLion 项目、`cmake-build-*`、`.idea/`、可执行文件或其他编译产物。
- `Lab6`、`Lab6.md`、`CMakeLists.txt` 和两个 `.c` 文件名的大小写必须完全一致。
- PR 标题必须严格使用 `[学号姓名]Lab6作业提交`，右方括号后不能有空格。
- 一个 PR 只能包含本次 Lab6 的文件，不得修改 Lab3、Lab4、Lab5、其他同学的文件、`homework/`、README 或仓库配置。

---

## 七、截止时间

**2026 年 9 月 28 日 24:00（即 2026 年 9 月 29 日 00:00，北京时间）**

以 GitHub 记录的最后一次向 PR 推送代码的时间为准。不晚于上述时刻创建 PR 并完成最后一次推送不算超时；超过该时刻新建 PR，或向已有 PR 推送任何修改，均算超时。审核未通过的同学请在截止前完成修改。
