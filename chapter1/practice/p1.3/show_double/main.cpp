#include<iostream>
#include"printint.h"
#include"printdouble.h"

int main(void)
{
    PrintInt(-123456);
    std::cout<<std::endl;
    PrintDouble(-3.1415926);

    std::cout<<std::endl;
    PrintInt(123456);
    std::cout<<std::endl;
    PrintDouble(3.1415926);
    return 0;
}
