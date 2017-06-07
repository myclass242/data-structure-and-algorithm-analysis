#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
template<typename object>
class Matrix
{
public:
    typedef object value_type;
    typedef typename std::vector<std::vector<object>>::size_type size_type;

    Matrix(size_type rows=0,size_type cols=0):matrix{rows}
    {
        for(auto &thisRow:matrix)
        {
            thisRow.resize(cols);
        }
    }

    Matrix(const Matrix&v):matrix{v.matrix}{}

    Matrix(Matrix &&v):matrix{std::move(v.matrix)}{}

    const std::vector<object> &operator[](size_type n) const;

    std::vector<object> &operator[](size_type n);

    size_type numRows() const
    {
        return matrix.size();
    }

    size_type numCols() const
    {
        return numRows()?matrix[0].size():0;
    }
private:
    std::vector<std::vector<object>> matrix;
};
#endif // MATRIX_H
