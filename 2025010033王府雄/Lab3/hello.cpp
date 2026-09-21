#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}

int main() {
    std::cout << "姓名: 王府雄" << std::endl;
    std::cout << "学号: 2025010033" << std::endl;

    bool isStudent = true;
    std::cout << "是否为学生: " << isStudent << std::endl;

    int id_last_two = 33;
    int result;
    bool success = getDoubled(id_last_two, result);
    std::cout << id_last_two << " 的两倍是 " << result << std::endl;

    return 0;
}
