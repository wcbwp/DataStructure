#include <iostream>

bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}
int main() {
    //1.输出姓名学号
    std::cout << "马潞怡" << std::endl;
    std::cout <<"2025010011" << std::endl;

    //2.定义一个bool变量，赋值为True
    bool isStudent = true;
    std::cout << isStudent << std::endl;

    int val =11;

    //res用来接收函数计算出来的翻倍结果
    int res;
    //调用引用参数函数
   bool result = getDoubled(val, res);

    std::cout << res << std::endl;
    return 0;
}



