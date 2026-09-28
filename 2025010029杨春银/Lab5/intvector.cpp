#include <iostream>

class IntVector {
private:
    int* data;
    int size;
    int capacity;

    // 有空位就直接返回；否则申请两倍容量，复制、释放、更新
    // 只改变空间，不改变 size 和已有元素的顺序
    void expand() {
        if (size<capacity) {
            return;      //有空位返回
        }// TODO：按 2.4 的步骤实现
        int newCapacity = capacity*2;
        int* newData = new int[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;      //释放旧数组
        data = newData;     //指向新数组
        capacity = newCapacity;     //更新容量
    }

public:
    explicit IntVector(int initialCapacity = 4) {
        if (initialCapacity < 1) {
            initialCapacity = 1;   //小于1统一调整为1
        }
        data = new int[initialCapacity];
        size = 0;
        capacity = initialCapacity;
        // TODO：把本函数体替换为正确的构造过程
        // 小于 1 的初始容量统一调整为 1
    }

    ~IntVector() {
        delete[] data;// TODO：释放当前动态数组
    }

    // 教师提供：禁止复制对象，原样保留，不考查完整语法
    IntVector(const IntVector&) = delete;
    IntVector& operator=(const IntVector&) = delete;

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;  // TODO
    }

    bool empty() const {
        return size == 0;
    }

    // 成功返回 true 并写入 value；非法下标返回 false，保持 value 不变
    bool get(int index, int& value) const {
        if (index < 0 || index >= size) {
            return false;
        }
        value = data[index];
        return true;  // TODO：迁移 Lab4
    }

    // 返回第一次出现的下标，未找到返回 -1
    int find(int value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;  // TODO：迁移 Lab4
    }

    // 先检查 0 <= index <= size，再 expand，再按 Lab4 的方向右移
    // 成功返回 true；非法下标返回 false，整个对象状态不变
    bool insert(int index, int value) {
        if (index < 0 || index > size) {
            return false;  // TODO：改造 Lab4
        }
        expand();
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size = size + 1;
        return true;
    }

    // 成功返回 true 并写入 removed；非法下标返回 false，保持 removed 不变
    // 本次不缩容，不在这里 delete[] data
    bool remove(int index, int& removed) {
        if (index < 0 || index >= size) {
            return false;
        }
        removed = data[index];
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size = size - 1;
        return true;  // TODO：迁移 Lab4
    }

    void pushBack(int value) {
        insert(size, value);// TODO：调用 insert(size, value)
    }

    // 元素之间一个空格，行首、行尾没有空格，最后换行；空表只输出换行
    void print() const {
        for (int i = 0; i < size; i++) {
            if (i > 0) {
                std::cout << " ";
            }
            std::cout << data[i];
        }
        std::cout << std::endl;  // TODO：迁移 Lab4，补上有效元素输出
    }
};

int main() {
    IntVector v;
    std::cout << "空表: size = " << v.getSize()
              << ", capacity = " << v.getCapacity()
              << ", empty = " << v.empty() << std::endl;

    int value = 777;
    bool ok = v.get(0, value);
    std::cout << "空表 get(0) 返回 " << ok << ", value = " << value << std::endl;
    int removed = 888;
    ok = v.remove(0, removed);
    std::cout << "空表 remove(0) 返回 " << ok << ", removed = " << removed << std::endl;

    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);
    v.pushBack(40);
    std::cout << "首次装满: size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;
    v.print();

    ok = v.insert(5, 99);
    std::cout << "满表 insert(5, 99) 返回 " << ok
              << ", size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;
    v.print();

    v.pushBack(50);
    std::cout << "追加 50 后: size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;
    v.print();

    ok = v.insert(0, 5);
    std::cout << "表头 insert(0, 5) 返回 " << ok << std::endl;
    v.print();
    ok = v.insert(3, 25);
    std::cout << "中间 insert(3, 25) 返回 " << ok << std::endl;
    v.print();
    ok = v.insert(v.getSize(), 60);
    std::cout << "表尾插入 60 返回 " << ok << std::endl;
    v.print();
    std::cout << "再次装满: size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;

    ok = v.insert(4, 28);
    std::cout << "满表 insert(4, 28) 返回 " << ok
              << ", size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;
    v.print();

    ok = v.remove(0, removed);
    std::cout << "remove(0) 返回 " << ok << ", removed = " << removed << std::endl;
    v.print();
    ok = v.remove(3, removed);
    std::cout << "remove(3) 返回 " << ok << ", removed = " << removed << std::endl;
    v.print();
    ok = v.remove(v.getSize() - 1, removed);
    std::cout << "删除表尾 返回 " << ok << ", removed = " << removed << std::endl;
    v.print();
    std::cout << "删除后: size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;

    ok = v.get(3, value);
    std::cout << "get(3) 返回 " << ok << ", value = " << value << std::endl;
    std::cout << "find(30) = " << v.find(30) << std::endl;
    std::cout << "find(99) = " << v.find(99) << std::endl;

    value = 777;
    ok = v.get(v.getSize(), value);
    std::cout << "get(size) 返回 " << ok << ", value = " << value << std::endl;
    ok = v.get(-1, value);
    std::cout << "get(-1) 返回 " << ok << ", value = " << value << std::endl;
    removed = 888;
    ok = v.remove(v.getSize(), removed);
    std::cout << "remove(size) 返回 " << ok << ", removed = " << removed << std::endl;
    ok = v.remove(-1, removed);
    std::cout << "remove(-1) 返回 " << ok << ", removed = " << removed << std::endl;
    ok = v.insert(-1, 99);
    std::cout << "insert(-1, 99) 返回 " << ok << std::endl;
    std::cout << "非法操作后: size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;
    v.print();

    for (int i = 0; i < 6; i++) {
        v.remove(0, removed);
    }
    std::cout << "删除全部: size = " << v.getSize()
              << ", capacity = " << v.getCapacity()
              << ", empty = " << v.empty() << std::endl;
    v.pushBack(-1);
    std::cout << "清空后追加: size = " << v.getSize()
              << ", capacity = " << v.getCapacity() << std::endl;
    v.print();

    IntVector small(0);
    std::cout << "初始容量传 0: size = " << small.getSize()
              << ", capacity = " << small.getCapacity() << std::endl;
    small.pushBack(7);
    small.pushBack(7);
    std::cout << "small: size = " << small.getSize()
              << ", capacity = " << small.getCapacity() << std::endl;
    small.print();
    std::cout << "small.find(7) = " << small.find(7) << std::endl;

    IntVector negative(-3);
    std::cout << "初始容量传 -3: size = " << negative.getSize()
              << ", capacity = " << negative.getCapacity() << std::endl;
    std::cout << "v 仍为: ";
    v.print();
    std::cout << "各对象的 size: " << v.getSize()
              << ' ' << small.getSize()
              << ' ' << negative.getSize() << std::endl;

    return 0;
}