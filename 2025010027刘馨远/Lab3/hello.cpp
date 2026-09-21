#include <iostream>

bool getDoubled(int value, int& result){
    result=value*2;
    return true;
}

int main(){
    std::cout<<"刘馨远"<< std::endl;
    std::cout<<"2025010027"<< std::endl;
    bool isStudent =true;
    std::cout<< isStudent << std::endl;
    
    int myValue=27;
    int result;
    getDoubled(myValue,result);
    std::cout<<result<<std::endl;
    return 0;
}