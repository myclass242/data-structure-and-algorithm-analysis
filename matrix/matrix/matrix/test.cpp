#include "test.h"
#include <iostream>

void TestAdd(void)
{
    Matrix A({ 1, 2, 3, 4, 5, 6 }, 2, 3, true);
    Matrix B({ 7, 8, 9, 10, 11, 12 }, 2, 3, true);
    Matrix C = A + B;
    
    std::cout << "Matrix A" << std::endl;
    std::cout << A << std::endl;
    std::cout << "plus Matrix B" << std::endl;
    std::cout << B << std::endl;
    std::cout << "equal to Matrix C" << std::endl;
    std::cout << C << std::endl;
}

void TestMinus(void)
{
    Matrix A({ 1, 2, 3, 4, 5, 6 }, 2, 3, true);
    Matrix B({ 7, 8, 9, 10, 11, 12 }, 2, 3, true);
    Matrix C = A - B;

    std::cout << "Matrix A" << std::endl;
    std::cout << A << std::endl;
    std::cout << "minus Matrix B" << std::endl;
    std::cout << B << std::endl;
    std::cout << "equal to Matrix C" << std::endl;
    std::cout << C << std::endl;
}

void TestMulti(void)
{
    Matrix A({ 1, 2, 3, 4, 5, 6 }, 2, 3, true);
    Matrix B({ 7, 8, 9, 10, 11, 12 }, 3, 2, true);

    Matrix C = A * B;
    std::cout << "Matrix A" << std::endl;
    std::cout << A << std::endl;
    std::cout << "multiply Matrix B" << std::endl;
    std::cout << B << std::endl;
    std::cout << "equal to Matrix C" << std::endl;
    std::cout << C << std::endl;

    Matrix D = A * A.transpose();
    std::cout << "Matrix A" << std::endl;
    std::cout << A << std::endl;
    std::cout << "multiply Matrix transpose A" << std::endl;
    std::cout << A.transpose() << std::endl;
    std::cout << "equal to Matrix D" << std::endl;
    std::cout << D << std::endl;

    Matrix E = Transpose(A) * A;
    std::cout << "Matrix transpose A" << std::endl;
    std::cout << Transpose(A) << std::endl;
    std::cout << "multiply Matrix A" << std::endl;
    std::cout << A << std::endl;
    std::cout << "equal to Matrix E" << std::endl;
    std::cout << E << std::endl;
}
