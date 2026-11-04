#pragma once

#include <stdint.h>
#include <iostream>

class BooleanVector
{
public:
    class BitReference;

    BooleanVector() = default;
    BooleanVector(const uint32_t numBits, const bool initialValue);

    uint32_t getBitsCount() const;

    void setValue(const uint32_t bitIndex, const bool newValue);

    bool operator[](const uint32_t bitIndex) const;
    BitReference operator[](const uint32_t bitIndex);

private:
    uint8_t* vectorData_ = nullptr;
    uint32_t numBits_ = 0;         
    uint32_t numBytes_ = 0;    
};

class BooleanVector::BitReference
{
public:
    BitReference(uint8_t* bytePtr, uint32_t bitIndex);

    operator bool();

    void operator=(const bool newValue);

private:
    uint8_t* bytePtr_;
    uint32_t bitIndex_;
};

std::istream& operator>>(std::istream& inputStream, BooleanVector& booleanVector);
std::ostream& operator<<(std::ostream& outputStream, const BooleanVector& booleanVector);
