# Lab4：从 C 顺序表到 C++ 固定容量向量类

## 一、配置 CMakeLists.txt
（已根据作业要求配置，见 CMakeLists.txt 文件）

## 二、完成本次作业所需的 C++ 知识
（已理解相关概念）

## 三、intvector.cpp：把 seqlist.c 改写为类
（已完成编写，见 intvector.cpp 文件）

## 四、选择题与填空

### 4.1 `private` 的作用
- [x] B. 编译错误，因为 `size` 是 `private` 成员，类外不能访问

### 4.2 构造函数
- [x] C. 它与类同名、没有返回类型，在 `IntVector v;` 创建对象时自动执行

### 4.3 成员函数的调用
- [x] B. `v.insert(2, 25)`

### 4.4 引用参数的调用
- [x] B. `v.remove(1, removed)`

### 4.5 成员函数末尾的 `const`
- [x] C. 这个函数不修改当前对象的 `data` 和 `size`

### 4.6 为什么需要 `getSize()`
- [x] B. `size` 是 `private` 的，类外读不到，`getSize()` 提供一个只读的入口

### 4.7 两个对象
- [x] B. `0`

### 4.8 算法与复杂度
- [x] B. 两者的元素移动过程和时间复杂度完全相同，只是代码组织方式不同

### 4.9 `get` 的返回值设计
- [x] A. `-1` 本身可能就是表中的一个元素，无法区分"读到了 `-1`"和"读取失败"

### 4.10 `find` 的返回值
- [x] B. `30` 在下标 `0` 处

### 4.11 填空：程序运行验证
- [x] A. 一致
- 填空内容：无

### 4.12 填空：C 与 C++ 写法的对应关系

| C（Lab3 / 课堂） | C++（本次作业） |
| :--- | :--- |
| `SeqList list; list.size = 0;` | `IntVector v;`（构造函数自动初始化 size 为 0） |
| `insertAt(&list, 2, 25)` | `v.insert(2, 25)` |
| `removeAt(&list, 1, &removed)` | `v.remove(1, removed)` |
| 函数体内的 `list->data[i]` | `data[i]` |
| 返回 `int` 的 `1` / `0` | 返回 `bool` 的 `true` / `false` |

### 4.13 填空：一句话总结
用一句话说明：为什么把 `size` 设为 `private` 之后，`insert`、`remove` 里的边界检查才真正"管用"？
回答：将 size 设为 private 后，外部无法直接修改 size，所有修改都必须通过成员函数进行，边界检查在成员函数内部执行，从而保证了数据完整性和边界检查的有效性。

---