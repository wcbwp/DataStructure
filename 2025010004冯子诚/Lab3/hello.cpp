#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    // 输出姓名和学号
    std::cout << "姓名: 冯子诚" << std::endl;
    std::cout << "学号: 2025010004" << std::endl;

    // 定义布尔变量并输出
    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    // 使用学号最后两位作为 value 调用 getDoubled
    int lastTwoDigits = 4; // 学号 2025010004 的最后两位是 04，即数值 4
    int result;
    getDoubled(lastTwoDigits, result);
    std::cout << lastTwoDigits << " 的两倍是 " << result << std::endl;

    return 0;
}