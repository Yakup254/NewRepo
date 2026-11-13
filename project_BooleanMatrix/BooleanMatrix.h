#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>

#include "solver_dynamic_array.h"
#include "BooleanVector.h"

class BooleanMatrix
{
public:
    BooleanMatrix() = default;
    BooleanMatrix(const uint32_t numRows, const uint32_t numCols, const bool initialValue = false);
    BooleanMatrix(const char** charMatrix, const uint32_t numRows, const uint32_t numCols);
    BooleanMatrix(const BooleanMatrix& other) = default;
    BooleanMatrix(BooleanMatrix&& other) noexcept = default;
    ~BooleanMatrix() = default;

    BooleanMatrix& operator=(const BooleanMatrix& other) = default;
    BooleanMatrix& operator=(BooleanMatrix&& other) noexcept = default;
    void swap(BooleanMatrix& other) noexcept;

    uint32_t getRowsCount() const;
    uint32_t getColumnsCount() const;

    uint32_t getWeight() const;

    BooleanVector& operator[](const uint32_t rowIndex);
    const BooleanVector& operator[](const uint32_t rowIndex) const;

private:
    DynamicArray<BooleanVector> matrixData_;
};

std::istream& operator>>(std::istream& inputStream, BooleanMatrix& matrix);
std::ostream& operator<<(std::ostream& outputStream, const BooleanMatrix& matrix);
