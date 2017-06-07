#include <iostream>
#include"intcell.h"

int main()
{
    IntCell ic1;
    std::cout<<ic1.read()<<std::endl;
    ic1.write(26);
    std::cout<<ic1.read()<<std::endl;

    IntCell ic2(13);
    std::cout<<ic2.read()<<std::endl;

    ic2=static_cast<IntCell>(23);
    std::cout<<ic2.read()<<std::endl;

    IntCell ic4{};
    std::cout<<ic4.read()<<std::endl;
    return 0;
}
