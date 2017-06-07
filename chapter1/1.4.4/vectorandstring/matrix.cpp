#include"matrix.h"

template<typename object>
const std::vector<object> &Matrix<object>::operator[](size_type n) const
{
    return matrix[n];
}

template<typename object>
std::vector<object> &Matrix<object>::operator[](size_type n)
{
    return matrix[n];
}

