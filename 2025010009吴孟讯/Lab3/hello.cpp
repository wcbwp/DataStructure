#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 吴孟讯" << std::endl;
    std::cout << "学号: 2025010009" << std::endl;
    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;
    int value = 9; // 学号最后两位
    int result;
    bool ok = getDoubled(value, result);
    std::cout << value << " 的两倍是 " << result << std::endl;
    return 0;
}