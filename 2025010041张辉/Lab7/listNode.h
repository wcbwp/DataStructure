#ifndef LISTNODE_H
#define LISTNODE_H

/* ==========================================================================
 * 邓俊辉《数据结构（C++ 语言版）》第三章：列表结点 ListNode
 * ========================================================================== */

template <typename T>
struct ListNode {
    T data;

    ListNode<T>* pred;
    ListNode<T>* succ;

    ListNode()
        : data(), pred(nullptr), succ(nullptr) {}

    ListNode(const T& e,
             ListNode<T>* p = nullptr,
             ListNode<T>* s = nullptr)
        : data(e), pred(p), succ(s) {}

    ListNode<T>* insertAsPred(const T& e);
    ListNode<T>* insertAsSucc(const T& e);
};

/* 练习 1：在自己前面插入 e。新结点 x 先抓住两边，再改老前驱与自己的指针 */
template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T& e) {
    ListNode<T>* x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

/* 练习 2：在自己后面插入 e。与练习 1 左右对称，pred 换 succ、this 换 succ */
template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T& e) {
    ListNode<T>* x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

#endif