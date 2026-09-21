//
// Created by 联想电脑 on 2026/9/9.
#include <iostream>
bool getDoubled(int value, int &result)
{
    result = value * 2;
    return true;
}
int main()
{
    std::cout << "姓名: 李苹" << std::endl;
    std::cout << "学号: 2025010013" << std::endl;
    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;
    int input = 13;
    int output;
    bool ok = getDoubled(input, output);
    std::cout << input << " 的两倍是 " << output << std::endl;
    return 0;
}