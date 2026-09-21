#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 李宇轩" << std::endl;
    std::cout << "学号: 2025010020" << std::endl;

    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    int lastTwo = 20;
    int doubled;
    getDoubled(lastTwo, doubled);
    std::cout << lastTwo << " 的两倍是 " << doubled << std::endl;

    return 0;
}
