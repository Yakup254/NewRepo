#include "BooleanVector.h"

BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
{
    numBits_ = numBits;

    if (numBits == 0)
    {
        numBytes_ = 0;
        vectorData_ = nullptr;
        return;
    }

    numBytes_ = (numBits + 7) / 8;
    vectorData_ = new uint8_t[numBytes_];

    for (uint32_t byteIndex = 0; byteIndex < numBytes_; byteIndex++)
    {
        vectorData_[byteIndex] = initialValue ? 0xFF : 0;
    }
}

uint32_t BooleanVector::getBitsCount() const
{
    return numBits_;
}

bool BooleanVector::operator[](const uint32_t bitIndex) const
{
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    return (vectorData_[byteIndex] & (1 << bitWithinByte)) != 0;
}

BooleanVector::BitReference BooleanVector::operator[](const uint32_t bitIndex)
{
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    return BitReference(&vectorData_[byteIndex], bitWithinByte);
}

void BooleanVector::setValue(const uint32_t bitIndex, const bool newValue)
{
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    if (newValue)
        vectorData_[byteIndex] |= (1 << bitWithinByte);
    else
        vectorData_[byteIndex] &= ~(1 << bitWithinByte);
}


BooleanVector::BitReference::BitReference(uint8_t* bytePtr, uint32_t bitIndex): bytePtr_(bytePtr), bitIndex_(bitIndex){}

BooleanVector::BitReference::operator bool()
{
    return (*bytePtr_ & (1 << bitIndex_)) != 0;
}

void BooleanVector::BitReference::operator=(const bool newValue)
{
    if (newValue)
        *bytePtr_ |= (1 << bitIndex_);
    else
        *bytePtr_ &= ~(1 << bitIndex_);
}


std::istream& operator>>(std::istream& inputStream, BooleanVector& booleanVector)
{
    uint32_t numBits;
    inputStream >> numBits;

    booleanVector = BooleanVector(numBits, false);

    for (uint32_t bitIndex = 0; bitIndex < numBits; bitIndex++)
    {
        uint32_t bitValue;
        inputStream >> bitValue;
        booleanVector.setValue(bitIndex, bitValue != 0);
    }

    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const BooleanVector& booleanVector)
{
    uint32_t numBits = booleanVector.getBitsCount();

    for (uint32_t bitIndex = 0; bitIndex < numBits; bitIndex++)
    {
        outputStream << (booleanVector[bitIndex] ? "1" : "0");
    }

    return outputStream;
}
