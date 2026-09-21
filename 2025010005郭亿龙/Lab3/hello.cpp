#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 郭亿龙" << std::endl;
    std::cout << "学号: 2025010005" << std::endl;

    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    int val = 05;   // 学号最后两位
    int res;
    bool ok = getDoubled(val, res);
    if (ok) {
        std::cout << val << " 的两倍是 " << res << std::endl;
    }
    return 0;
}
