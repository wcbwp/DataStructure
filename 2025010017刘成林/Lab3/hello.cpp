#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 刘成林" << std::endl;
    std::cout << "学号: 2025010017" << std::endl;
    
    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;
    
    int number = 17;
    int doubled;
    getDoubled(number, doubled);
    std::cout << number << " 的两倍是 " << doubled << std::endl;
    
    return 0;
}