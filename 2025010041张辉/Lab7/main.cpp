/* ==========================================================================
 * Lab7 测试程序：课本版 List<T>（listNode.h + list.h）的统一测试
 * ========================================================================== */

#include <iostream>
#include "list.h"

static void testIntList() {
    List<int> list;

    std::cout << "after init: ";
    list.print();
    std::cout << "empty = " << list.empty() << ", size = " << list.size() << "\n\n";

    int samples[] = {18, -1, 42, 18, 65};
    for (int i = 0; i < 5; i++) {
        list.insertAsLast(samples[i]);
    }
    std::cout << "after insertAsLast 18, -1, 42, 18, 65: ";
    list.print();
    std::cout << '\n';

    bool ok = list.insert(2, 25);
    std::cout << "insert(2, 25): ok = " << ok << ", ";
    list.print();

    int removed = 777;
    ok = list.remove(1, removed);
    std::cout << "remove(1): ok = " << ok << ", removed = " << removed << ", ";
    list.print();

    list.insertAsFirst(7);
    std::cout << "insertAsFirst(7): ";
    list.print();
    std::cout << '\n';

    int value = 777;
    ok = list.get(0, value);
    std::cout << "get(0): ok = " << ok << ", value = " << value << '\n';

    value = 777;
    ok = list.get(6, value);
    std::cout << "get(6): ok = " << ok << ", value = " << value << "\n\n";

    std::cout << "rankOf(find(42)) = " << list.rankOf(list.find(42)) << '\n';
    std::cout << "rankOf(find(18)) = " << list.rankOf(list.find(18)) << '\n';
    std::cout << "rankOf(find(99)) = " << list.rankOf(list.find(99)) << "\n\n";

    ListNode<int>* p = list.first();
    list.insertB(p, 2000);
    list.insertA(p, 1000);
    std::cout << "insertB(first(), 2000) and insertA(first(), 1000): ";
    list.print();
    std::cout << '\n';

    std::cout << "list[2]->data = " << list[2]->data << '\n';
    list.printReverse();
    std::cout << '\n';

    ok = list.insert(-1, 100);
    std::cout << "insert(-1, 100): ok = " << ok << '\n';
    ok = list.insert(100, 100);
    std::cout << "insert(100, 100): ok = " << ok << '\n';

    List<int> empty;
    ok = empty.remove(0, removed);
    std::cout << "empty remove(0): ok = " << ok << "\n\n";

    std::cout << "remove one by one: ";
    for (int i = 0; i < 3; i++) {
        list.remove(0, removed);
        std::cout << removed << "(size = " << list.size() << ") ";
    }
    std::cout << "\nbefore leaving testIntList: ";
    list.print();
    std::cout << "no listDestroy written by hand: both objects clean themselves up ->\n";
}

static void testDoubleList() {
    List<double> nums;

    double values[] = {1.5, 2.25, -3.75};
    for (int i = 0; i < 3; i++) {
        nums.insertAsLast(values[i]);
    }
    std::cout << "List<double>: ";
    nums.print();

    nums.insert(1, 0.5);
    std::cout << "after insert(1, 0.5): ";
    nums.print();

    double firstValue = 0.0;
    nums.get(0, firstValue);
    std::cout << "get(0) = " << firstValue << ", size = " << nums.size() << '\n';
}

int main() {
    std::cout << "sizeof(ListNode<int>) = " << sizeof(ListNode<int>) << '\n';
    std::cout << "sizeof(List<int>) = " << sizeof(List<int>) << "\n\n";

    testIntList();
    std::cout << '\n';
    testDoubleList();
    return 0;
}