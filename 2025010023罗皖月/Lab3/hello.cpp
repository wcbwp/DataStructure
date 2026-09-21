#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 罗皖月" << std::endl;
    std::cout << "学号: 2025010023" << std::endl;

    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    int result = 0;
    getDoubled(23, result);
    std::cout << "23 的两倍是 " << result << std::endl;

    return 0;
}