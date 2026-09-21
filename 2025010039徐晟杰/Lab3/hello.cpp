#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 徐晟杰" << std::endl;
    std::cout << "学号: 2025010039" << std::endl;

    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    int result = 0;
    if (getDoubled(39, result)) {
        std::cout << "39 的两倍是 " << result << std::endl;
    }
    return 0;
}