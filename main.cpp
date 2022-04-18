#include<iostream>
#include<string>
#include<time.h>
int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "git好" << std::endl;
    // 获取当前系统时间
    time_t t = time(0);
    // 将时间转换为字符串
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    std::cout << tmp << std::endl;
    std::cout << "新功能test1.1" << std::endl;
    std::cout << "另一个人的提交" << std::endl;
    std::cout << "我的提交" << std::endl;
    std::cout << "另一个人的提交2" << std::endl;
    return 0;
}
