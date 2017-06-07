#include <iostream>
#include<vector>
#include"sort.h"
int main()
{
    std::vector<int> vi1{7,2,5,4,9,8,6,9,4};
    std::vector<int> vi2=vi1;
    std::cout<<SelectBigN(vi1,3,vi1.size())<<std::endl;

    BubbleSort(vi1,vi1.size());
    InsertSort(vi2,vi2.size());

    for(const auto &i:vi1)
    {
        std::cout<<i<<' ';
    }
    std::cout<<std::endl;

    for(const auto &i:vi2)
    {
        std::cout<<i<<' ';
    }
    std::cout<<std::endl;

    return 0;
}
