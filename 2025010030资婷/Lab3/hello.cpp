#include <iostream>
int getDoubled(int value, int& result) {
    result = value * 2;  // 必须解引用才能写回
    return true;  // 成功
}
int main() {
    char name[] = "资婷";
    long long id =2025010030;
    std::cout << "姓名: " << name << std::endl;
    std::cout << "学号: " << id << std::endl;
    bool isStudent = true;
    std::cout << "是否是学生: " << isStudent << std::endl;
    int value = id%100;
    int res;
    getDoubled(value,res);
    std::cout << value <<  " 的两倍是 "  << res << std::endl;
    std::cin.get();
    return 0;
}
// Created by 荣耀 on 2026/9/9.
//
