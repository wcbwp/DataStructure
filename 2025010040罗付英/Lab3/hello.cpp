#include <iostream>
using namespace std;
bool getDoubled(int value, int& result) {
    result = value * 2;
    return true;
}
int main() {
    int a=1;
    int b;
    cout<<"姓名：罗付英"<<endl;
    cout<<"学号：2025010040"<<endl;
    cout<<"是否为学生：1"<<endl;
    getDoubled(a,b);
    cout<<a<<" 的两倍是 "<<b<<endl;
    return 0;
}