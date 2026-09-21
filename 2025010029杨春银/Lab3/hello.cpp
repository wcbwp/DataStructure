#include <iostream>

// 引用参数版本：计算 value * 2 存入 result，返回 true
bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    // 1. 输出姓名和学号（请替换成你自己的真实信息）
    std::cout << "姓名: 杨春银" << std::endl;
    std::cout << "学号: 2025010029*" << std::endl;

    // 2. bool 变量
    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    // 3. 调用 getDoubled，用学号最后两位作为 value
    int input = 1;   // 请改成你学号的最后两位
    int output = 0;
    bool ok = getDoubled(input, output);
    if (ok) {
        std::cout << input << " 的两倍是 " << output << std::endl;
    }

    return 0;
}