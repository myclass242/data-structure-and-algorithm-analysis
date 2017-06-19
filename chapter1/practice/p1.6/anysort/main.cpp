#include <iostream>
#include"permute.h"

int main()
{
    std::vector<std::string> vs1 = permute("abcd");
    for(const auto &i:vs1)
    {
        std::cout<<i<<std::endl;
    }
    return 0;
}
