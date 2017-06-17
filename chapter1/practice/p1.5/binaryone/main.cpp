#include"binaryone.h"
#include <iostream>

int main()
{
    int num;
    std::cout<<"Please enter a num,then i will show you the total binary one in the number:";
    std::cin>>num;
    std::cout<<NumsOfBinaryOne(num)<<" binary one in "<<num<<std::endl;
    return 0;
}
