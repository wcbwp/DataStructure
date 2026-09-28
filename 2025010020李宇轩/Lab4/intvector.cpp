#include <iostream>

#define MAX_SIZE 100

class IntVector {
private:
    int data[MAX_SIZE];
    int size;

public:
    IntVector() {
        size = 0;
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    bool get(int index, int& value) const {
        if (index < 0 || index >= size) {
            return false;
        }
        value = data[index];
        return true;
    }

    int find(int value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    bool insert(int index, int value) {
        if (size == MAX_SIZE) {
            return false;
        }
        if (index < 0 || index > size) {
            return false;
        }
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
        return true;
    }

    bool remove(int index, int& removed) {
        if (index < 0 || index >= size) {
            return false;
        }
        removed = data[index];
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
        return true;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            if (i > 0) {
                std::cout << " ";
            }
            std::cout << data[i];
        }
        std::cout << std::endl;
    }
};

int main() {
    IntVector v;
    std::cout << "空表: size = " << v.getSize() << ", empty = " << v.empty() << std::endl;

    v.insert(0, 10);
    v.insert(1, 20);
    v.insert(2, 30);
    v.insert(3, 40);
    std::cout << "初始: ";
    v.print();

    bool ok = v.insert(2, 25);
    std::cout << "insert(2, 25) 返回 " << ok << std::endl;
    v.print();

    int removed = 0;
    ok = v.remove(1, removed);
    std::cout << "remove(1) 返回 " << ok << ", 删除的值是 " << removed << std::endl;
    v.print();

    ok = v.insert(10, 99);
    std::cout << "insert(10, 99) 返回 " << ok << std::endl;
    v.print();

    ok = v.remove(4, removed);
    std::cout << "remove(4) 返回 " << ok << std::endl;
    v.print();

    int value = 0;
    ok = v.get(2, value);
    std::cout << "get(2) 返回 " << ok << ", value = " << value << std::endl;
    ok = v.get(4, value);
    std::cout << "get(4) 返回 " << ok << std::endl;

    std::cout << "find(30) = " << v.find(30) << std::endl;
    std::cout << "find(99) = " << v.find(99) << std::endl;
    std::cout << "最终: size = " << v.getSize() << ", empty = " << v.empty() << std::endl;

    IntVector other;
    other.insert(0, 7);
    std::cout << "other: ";
    other.print();
    std::cout << "两个对象的 size: " << v.getSize() << " " << other.getSize() << std::endl;

    return 0;
}
