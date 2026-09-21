#include <iostream>

bool getDoubled(int value, int & result)
{
    result = value * 2;
    return true;
}

int main()
{
    std::cout << "姓名：陈星妤" << std::endl;
    std::cout << "学号：2025010015" << std::endl;

    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    int num = 15;
    int res;
    getDoubled(num, res);
    std::cout << num << " 的两倍是" << res << std::endl;

    return 0;
}