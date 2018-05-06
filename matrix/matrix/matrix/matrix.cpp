#include "matrix.h"
#include <cstdlib>
#include <iostream>

Matrix::Matrix(std::size_t rowNum, std::size_t colNum)
    :rowNum(rowNum), colNum(colNum)
{
    array.resize(colNum);
    for (std::size_t colIdx = 1; colIdx <= colNum; ++colIdx)
    {
        array[colIdx - 1].resize(rowNum);
        for (std::size_t rowIdx = 1; rowIdx <= rowNum; ++rowIdx)
        {
            array[colIdx - 1][rowIdx - 1] = 0;
        }
    }
}

Matrix::Matrix(const std::vector<double> &sequence, std::size_t rowNum, std::size_t colNum, bool byRow)
    :rowNum(rowNum), colNum(colNum)
{
    if (byRow)
    {
        constructMatrixByRow(sequence);
    }
    else
    {
        constructMatrixByCol(sequence);
    }
}

Matrix::Matrix(const std::vector<double>& sequence, bool byRow)
{
    if (byRow)
    {
        rowNum = 1;
        colNum = sequence.size();
        constructMatrixByRow(sequence);
    }
    else
    {
        rowNum = sequence.size();
        colNum = 1;
        constructMatrixByCol(sequence);
    }
}

Matrix::Matrix(const Matrix & rhs)
    :rowNum(rhs.rowNum), colNum(rhs.colNum), array(rhs.array)
{
}

Matrix::Matrix(Matrix && rhs)
    : rowNum(rhs.rowNum), colNum(rhs.colNum), array(std::move(rhs.array))
{
}

Matrix & Matrix::operator=(const Matrix & rhs)
{
    rowNum = rhs.rowNum;
    colNum = rhs.colNum;
    array = rhs.array;
    
    return *this;
}

Matrix & Matrix::operator=(Matrix && rhs)
{
    rowNum = rhs.rowNum;
    colNum = rhs.colNum;
    array = std::move(rhs.array);

    return *this;
}

std::vector<double>& Matrix::operator[](std::size_t colIdx)
{
    return array[colIdx];
}

std::ostream & operator<<(std::ostream &out, const Matrix &matrix)
{
    for (std::size_t rowIdx = 1; rowIdx <= matrix.rowNum; ++rowIdx)
    {
        for (std::size_t colIdx = 1; colIdx <= matrix.colNum; ++colIdx)
        {
            out << "  " << matrix.array[colIdx - 1][rowIdx - 1];
        }
        out << std::endl;
    }
    return out;
}

Matrix Matrix::transpose(void) const
{
    Matrix result(colNum, rowNum);
    for (std::size_t colIdx = 1; colIdx <= colNum; ++colIdx)
    {
        for (std::size_t rowIdx = 1; rowIdx <= rowNum; ++rowIdx)
        {
            result.array[rowIdx - 1][colIdx - 1] = array[colIdx - 1][rowIdx - 1];
        }
    }

    return result;
}

Matrix::~Matrix()
{
}

void Matrix::constructMatrixByRow(const std::vector<double>& sequence)
{
    array.resize(colNum);
    auto seqIte = sequence.begin();

    for (auto &col : array)
    {
        col.resize(rowNum);
    }

    for (std::size_t rowIdx = 1; rowIdx <= rowNum; ++rowIdx)
    {
        for (std::size_t colIdx = 1; colIdx <= colNum; ++colIdx)
        {
            if (sequence.end() == seqIte)
            {
                seqIte = sequence.begin();
            }
            array[colIdx - 1][rowIdx - 1] = *seqIte;
            ++seqIte;
        }
    }
}

void Matrix::constructMatrixByCol(const std::vector<double>& sequence)
{
    array.resize(colNum);
    auto seqIte = sequence.begin();

    for (std::size_t colIdx = 1; colIdx <= colNum; ++colIdx)
    {
        array[colIdx - 1].resize(rowNum);
        for (std::size_t rowIdx = 1; rowIdx <= rowNum; ++rowIdx)
        {
            if (sequence.end() == seqIte)
            {
                seqIte = sequence.begin();
            }
            array[colIdx - 1][rowIdx - 1] = *seqIte;
            ++seqIte;
        }
    }
}

Matrix operator+(const Matrix & lhs, const Matrix & rhs)
{
    if (!matrixAddValid(lhs, rhs))
    {
        std::cout << "Matrix Add INVALID" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Matrix temp = lhs;
    for (std::size_t colIdx = 1; colIdx <= temp.colNum; ++colIdx)
    {
        for (std::size_t rowIdx = 1; rowIdx <= temp.rowNum; ++rowIdx)
        {
            temp.array[colIdx - 1][rowIdx - 1] += rhs.array[colIdx - 1][rowIdx - 1];
        }
    }
    return temp;
}

Matrix operator-(const Matrix & lhs, const Matrix & rhs)
{
    return lhs + (-1.0) * rhs;
}

Matrix operator*(const Matrix & lhs, const Matrix & rhs)
{
    if (!matrixMultiValid(lhs, rhs))
    {
        std::cout << "Matrix Multiply INVALID" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Matrix result(lhs.rowNum, rhs.colNum);
    Matrix temp;
    for (std::size_t colIdx = 1; colIdx <= rhs.colNum; ++colIdx)
    {
        temp = std::move(lhs * rhs.array[colIdx - 1]);
        result[colIdx - 1] = temp.array[0];
    }
    return result;
}

Matrix operator*(const Matrix & matrix, const std::vector<double>& vector)
{
    if (!matrixMultiValid(matrix, vector))
    {
        std::cout << "Matrix Multiply INVALID" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Matrix temp(matrix.rowNum, 1);
    for (std::size_t colIdx = 1; colIdx <= matrix.colNum; ++colIdx)
    {
        temp = temp + static_cast<Matrix>(matrix.array[colIdx - 1]) * vector[colIdx - 1];
    }
    return temp;
}

Matrix operator*(const Matrix & matrix, double c)
{
    Matrix temp = matrix;
    for (std::size_t colIdx = 1; colIdx <= temp.colNum; ++colIdx)
    {
        for (std::size_t rowIdx = 1; rowIdx <= temp.rowNum; ++rowIdx)
        {
            temp.array[colIdx - 1][rowIdx - 1] *= c;
        }
    }
    return temp;
}

Matrix operator*(double c, const Matrix & matrix)
{
    return matrix * c;
}

Matrix Transpose(const Matrix & matrix)
{
    return matrix.transpose();
}

bool matrixAddValid(const Matrix & lhs, const Matrix & rhs)
{
    return lhs.rowNum == rhs.rowNum && lhs.colNum == rhs.colNum;
}

bool matrixMultiValid(const Matrix & lhs, const Matrix & rhs)
{
    return lhs.colNum == rhs.rowNum;
}

bool matrixMultiValid(const Matrix & matrix, const std::vector<double>& vector)
{
    return matrix.colNum == vector.size();
}
