#pragma once
#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <utility>
#include <ostream>

class Matrix
{
public:
    explicit Matrix(std::size_t rowNum = 1, std::size_t colNum = 1);
    Matrix(const std::vector<double> &sequence, std::size_t rowNum, std::size_t colNum, bool byRow = false);
    Matrix(const std::vector<double> &sequence, bool byRow = false);
    Matrix(const Matrix &rhs);
    Matrix(Matrix &&rhs);
    Matrix &operator=(const Matrix &rhs);
    Matrix &operator=(Matrix &&rhs);
    std::vector<double> &operator[](std::size_t colIdx);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
    friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);
    friend Matrix operator-(const Matrix &lhs, const Matrix &rhs);
    friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);
    friend Matrix operator*(const Matrix &matrix, const std::vector<double> &vector);
    friend Matrix operator*(const Matrix &matrix, double c);
    friend Matrix operator*(double c, const Matrix &matrix);
    Matrix transpose(void) const;
    friend Matrix Transpose(const Matrix &matrix);
    ~Matrix();
private:
    void constructMatrixByRow(const std::vector<double> &sequence);
    void constructMatrixByCol(const std::vector<double> &sequence);
    friend bool matrixAddValid(const Matrix &lhs, const Matrix &rhs);
    friend bool matrixMultiValid(const Matrix &lhs, const Matrix &rhs);
    friend bool matrixMultiValid(const Matrix &matrix, const std::vector<double> &vector);
private:
    std::vector<std::vector<double>> array;
    std::size_t rowNum;
    std::size_t colNum;
};

#endif
