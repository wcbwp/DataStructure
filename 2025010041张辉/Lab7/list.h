#ifndef LIST_H
#define LIST_H

/* ==========================================================================
 * 邓俊辉《数据结构（C++ 语言版）》第三章：列表 List
 * ========================================================================== */

#include <iostream>
#include "listNode.h"

typedef int Rank;

template <typename T>
class List {
private:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;

protected:
    void init();
    int clear();

public:
    List() { init(); }
    ~List();

    Rank size() const { return _size; }
    bool empty() const { return _size == 0; }
    ListNode<T>* first() const { return header->succ; }
    ListNode<T>* last() const { return trailer->pred; }
    bool valid(ListNode<T>* p) const {
        return p != nullptr && p != header && p != trailer;
    }

    ListNode<T>* insertAsFirst(const T& e);
    ListNode<T>* insertAsLast(const T& e);
    ListNode<T>* insertA(ListNode<T>* p, const T& e);
    ListNode<T>* insertB(ListNode<T>* p, const T& e);

    T remove(ListNode<T>* p);

    ListNode<T>* find(const T& e) const;
    ListNode<T>* operator[](Rank r) const;
    Rank rankOf(ListNode<T>* p) const;

    bool insert(Rank r, const T& e);
    bool remove(Rank r, T& e);
    bool get(Rank r, T& e) const;

    void print() const;
    void printReverse() const;
};

/* 教师提供：建立空表 */
template <typename T>
void List<T>::init() {
    header = new ListNode<T>();
    trailer = new ListNode<T>();
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

/* 练习 3：删除全部有效结点，保留两个哨兵，返回删掉的个数。靠 _size>0 停止 */
template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (_size > 0) {
        remove(header->succ);
    }
    return oldSize;
}

/* 教师提供：析构函数 */
template <typename T>
List<T>::~List() {
    int n = clear();
    delete header;
    delete trailer;
    std::cout << "(destructor: cleared " << n << " data nodes, freed 2 sentinels)\n";
}

/* 教师提供：作为首元素插入 */
template <typename T>
ListNode<T>* List<T>::insertAsFirst(const T& e) {
    return insertB(first(), e);
}

/* 教师提供：作为末元素插入 */
template <typename T>
ListNode<T>* List<T>::insertAsLast(const T& e) {
    return insertB(trailer, e);
}

/* 练习 4a：作为 p 的后继插入，复用 insertAsSucc，_size 由 List 维护 */
template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, const T& e) {
    _size++;
    return p->insertAsSucc(e);
}

/* 练习 4b：作为 p 的前驱插入，复用 insertAsPred */
template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, const T& e) {
    _size++;
    return p->insertAsPred(e);
}

/* 练习 5：删除结点 p，先取 data，再断链两句，最后单独 delete，再 _size-- */
template <typename T>
T List<T>::remove(ListNode<T>* p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

/* 练习 6：按值查找，从末结点顺 pred 往前走，遇到 header 没找到 */
template <typename T>
ListNode<T>* List<T>::find(const T& e) const {
    for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
        if (p->data == e) {
            return p;
        }
    }
    return nullptr;
}

/* 练习 7：按秩定位，从首结点走 r 步；越界返回 nullptr */
template <typename T>
ListNode<T>* List<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size) {
        return nullptr;
    }
    ListNode<T>* p = header->succ;
    for (Rank i = 0; i < r; i++) {
        p = p->succ;
    }
    return p;
}

/* 教师提供：位置折算成秩 */
template <typename T>
Rank List<T>::rankOf(ListNode<T>* p) const {
    if (!valid(p)) {
        return -1;
    }
    Rank r = 0;
    for (ListNode<T>* q = first(); q != p; q = q->succ) {
        r++;
    }
    return r;
}

/* 练习 8a：秩 r 处插入，0<=r<=size；r==size 时目标是尾哨兵 trailer */
template <typename T>
bool List<T>::insert(Rank r, const T& e) {
    if (r < 0 || r > _size) {
        return false;
    }
    ListNode<T>* p = (r == _size) ? trailer : (*this)[r];
    insertB(p, e);
    return true;
}

/* 练习 8b：删除秩 r 处，数据经 e 带回；越界不修改 e */
template <typename T>
bool List<T>::remove(Rank r, T& e) {
    if (r < 0 || r >= _size) {
        return false;
    }
    e = remove((*this)[r]);
    return true;
}

/* 练习 8c：按秩读取，失败不修改 e */
template <typename T>
bool List<T>::get(Rank r, T& e) const {
    if (r < 0 || r >= _size) {
        return false;
    }
    e = (*this)[r]->data;
    return true;
}

/* 教师提供：正向遍历 */
template <typename T>
void List<T>::print() const {
    std::cout << "[size = " << _size << "] ";
    for (ListNode<T>* p = header->succ; p != trailer; p = p->succ) {
        std::cout << p->data << ' ';
    }
    std::cout << '\n';
}

/* 练习 9：反向遍历，从 trailer->pred 出发，遇 header 停 */
template <typename T>
void List<T>::printReverse() const {
    std::cout << "[size = " << _size << "] reverse: ";
    for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
        std::cout << p->data << ' ';
    }
    std::cout << '\n';
}

#endif