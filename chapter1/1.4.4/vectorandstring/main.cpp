#include <iostream>
#include<vector>
#include<functional>
#include"matrix.h"

int main()
{
    std::vector<int> squares(100);
    //auto squaresSize=squares.size();
    //squares::size_type squaresSize=squares.size();
    decltype(squares)::size_type squaresSize=squares.size();
    for(decltype(squaresSize) n=0;n<squaresSize;++n)
    {
        squares[n] = n * n;
    }
   /*
    for(auto &elem:squares)
    {
        std::cout<<elem<<std::endl;
    }
    */


    //Matrix
    Matrix<int> array(4,5);
    auto numRowsInArray=array.numRows();
    auto numColsInArray=array.numCols();
    for(decltype(array)::size_type i=0;i<numRowsInArray;++i)
    {
        for(decltype(i) j=0;j<numColsInArray;++j)
        {
            array[i][j]=i*j;
        }
    }
    for(decltype(array)::size_type i=0;i<numRowsInArray;++i)
    {
        for(decltype(i) j=0;j<numColsInArray;++j)
        {
            std::cout<<array[i][j]<<' ';
        }
        std::cout<<std::endl;
    }

    return 0;
}
