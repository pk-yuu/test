#include<iostream>
#include<string>
#include<time.h>
int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "git��" << std::endl;
    // ��ȡ��ǰϵͳʱ��
    time_t t = time(0);
    // ��ʱ��ת��Ϊ�ַ���
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    std::cout << tmp << std::endl;
    std::cout << "�¹���test1.1" << std::endl;
    return 0;
}