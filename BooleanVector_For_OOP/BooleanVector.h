#pragma once

#include <stdint.h>
#include <iostream>
#include <cassert>

class BooleanVector
{
public:
    class BitReference;

    BooleanVector();
    BooleanVector(const uint32_t numBits, const bool initialValue = false);
    BooleanVector(const char* bitString);
    BooleanVector(const BooleanVector& other);
    BooleanVector(BooleanVector&& other) noexcept;
    ~BooleanVector();

    BooleanVector& operator=(const BooleanVector& other);
    BooleanVector& operator=(BooleanVector&& other) noexcept;

    uint32_t getBitsCount() const;
    uint32_t weight() const;

    bool getBit(const uint32_t bitIndex) const;
    void setValue(const uint32_t bitIndex, const bool newValue);
    void setRange(const uint32_t startIndex, const uint32_t count, const bool newValue);
    void setAll(const bool newValue);
    void invertAll();
    void invertBit(const uint32_t bitIndex);
    void swap(BooleanVector& other) noexcept;


    bool operator[](const uint32_t bitIndex) const;
    BitReference operator[](const uint32_t bitIndex);

    BooleanVector operator~() const;

    BooleanVector operator&(const BooleanVector& other) const;
    BooleanVector& operator&=(const BooleanVector& other);

    BooleanVector operator|(const BooleanVector& other) const;
    BooleanVector& operator|=(const BooleanVector& other);

    BooleanVector operator^(const BooleanVector& other) const;
    BooleanVector& operator^=(const BooleanVector& other);

    BooleanVector operator<<(const uint32_t shiftCount) const;
    BooleanVector& operator<<=(const uint32_t shiftCount);

    BooleanVector operator>>(const uint32_t shiftCount) const;
    BooleanVector& operator>>=(const uint32_t shiftCount);

    bool operator==(const BooleanVector& other) const;
    bool operator!=(const BooleanVector& other) const;


private:
    uint8_t* vectorData_ = nullptr;
    uint32_t numBits_ = 0;
    uint32_t numBytes_ = 0;


    uint32_t getBytesCount() const;
    void clearUnusedBits();
};

class BooleanVector::BitReference
{
public:
    BitReference(uint8_t* bytePtr, const uint32_t bitIndex);

    operator bool() const;

    BitReference& operator=(const bool newValue);
    BitReference& operator=(const BitReference& rhs);

    BitReference& operator&=(const bool val);
    BitReference& operator|=(const bool val);
    BitReference& operator^=(const bool val);

private:
    uint8_t* bytePtr_ = nullptr;
    uint32_t bitIndex_ = 0;
};

std::istream& operator>>(std::istream& inputStream, BooleanVector& booleanVector);
std::ostream& operator<<(std::ostream& outputStream, const BooleanVector& booleanVector);
