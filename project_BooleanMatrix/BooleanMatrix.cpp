#include "BooleanMatrix.h"

BooleanMatrix::BooleanMatrix(const uint32_t numRows, const uint32_t numCols, const bool initialValue)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        matrixData_ += BooleanVector(numCols, initialValue);
    }
}

BooleanMatrix::BooleanMatrix(const char** charMatrix, const uint32_t numRows, const uint32_t numCols)
{
    assert((charMatrix != nullptr || numRows == 0) && "Null charMatrix pointer.");

    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        assert(charMatrix[rowIndex] != nullptr && "Null row pointer in charMatrix.");
        BooleanVector row(numCols, false);

        for (uint32_t colIndex = 0; colIndex < numCols; ++colIndex)
        {
            char c = charMatrix[rowIndex][colIndex];
            assert((c == '0' || c == '1') && "Matrix characters must be '0' or '1'.");
            if (c == '1')
            {
                row.setValue(colIndex, true);
            }
        }
        matrixData_ += std::move(row);
    }
}

void BooleanMatrix::swap(BooleanMatrix& other) noexcept
{
    matrixData_.swap(other.matrixData_);
}

uint32_t BooleanMatrix::getRowsCount() const
{
    return static_cast<uint32_t>(matrixData_.getLength());
}

uint32_t BooleanMatrix::getColumnsCount() const
{
    if (matrixData_.getLength() == 0)
    {
        return 0;
    }
    return matrixData_[0].getBitsCount();
}

uint32_t BooleanMatrix::getWeight() const
{
    uint32_t totalWeight = 0;
    const uint32_t numRows = getRowsCount();

    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        totalWeight += matrixData_[rowIndex].weight();
    }
    return totalWeight;
}


BooleanVector& BooleanMatrix::operator[](const uint32_t rowIndex)
{
    assert(rowIndex < getRowsCount() && "Row index is out of range.");
    return matrixData_[rowIndex];
}

const BooleanVector& BooleanMatrix::operator[](const uint32_t rowIndex) const
{
    assert(rowIndex < getRowsCount() && "Row index is out of range.");
    return matrixData_[rowIndex];
}



std::istream& operator>>(std::istream& inputStream, BooleanMatrix& matrix)
{
    uint32_t numRows = 0;
    uint32_t numCols = 0;

    if (!(inputStream >> numRows >> numCols))
    {
        return inputStream;
    }

    BooleanMatrix tempMatrix(numRows, numCols, false);

    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        for (uint32_t colIndex = 0; colIndex < numCols; ++colIndex)
        {
            char bitChar;
            inputStream >> bitChar;
            assert((bitChar == '0' || bitChar == '1') && "Invalid character: expected '0' or '1'.");
            tempMatrix[rowIndex].setValue(colIndex, bitChar == '1');
        }
    }

    matrix.swap(tempMatrix);
    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const BooleanMatrix& matrix)
{
    const uint32_t numRows = matrix.getRowsCount();

    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        outputStream << matrix[rowIndex] <<std::endl;
    }

    return outputStream;
}