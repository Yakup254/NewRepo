#include "BooleanVector.h"
#include <algorithm>


BooleanVector::BooleanVector()
    : vectorData_(nullptr), numBits_(0), numBytes_(0)
{
}

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

    uint8_t fillByte = initialValue ? 0xFF : 0x00;
    for (uint32_t byteIndex = 0; byteIndex < numBytes_; ++byteIndex)
    {
        vectorData_[byteIndex] = fillByte;
    }
    clearUnusedBits();
}

BooleanVector::BooleanVector(const char* bitString)
{
    if (bitString == nullptr)
    {
        numBits_ = 0;
        numBytes_ = 0;
        vectorData_ = nullptr;
        return;
    }

    uint32_t length = 0;
    while (bitString[length] != '\0')
    {
        length++;
    }

    numBits_ = length;
    numBytes_ = (numBits_ + 7) / 8;
    vectorData_ = new uint8_t[numBytes_](); 

    for (uint32_t i = 0; i < numBits_; ++i)
    {
        if (bitString[i] == '1')
        {
            setValue(i, true);
        }
    }
    clearUnusedBits();
}

BooleanVector::BooleanVector(const BooleanVector& other)
    : numBits_(other.numBits_), numBytes_(other.numBytes_)
{
    if (numBytes_ > 0)
    {
        vectorData_ = new uint8_t[numBytes_];
        for (uint32_t i = 0; i < numBytes_; ++i)
        {
            vectorData_[i] = other.vectorData_[i];
        }
    }
}

BooleanVector::BooleanVector(BooleanVector&& other) noexcept
    : vectorData_(other.vectorData_), numBits_(other.numBits_), numBytes_(other.numBytes_)
{
    other.vectorData_ = nullptr;
    other.numBits_ = 0;
    other.numBytes_ = 0;
}

BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
}


BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
    if (this != &other)
    {
        delete[] vectorData_;

        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;

        if (numBytes_ > 0)
        {
            vectorData_ = new uint8_t[numBytes_];
            for (uint32_t i = 0; i < numBytes_; ++i)
            {
                vectorData_[i] = other.vectorData_[i];
            }
        }
        else
        {
            vectorData_ = nullptr;
        }
    }
    return *this;
}

BooleanVector& BooleanVector::operator=(BooleanVector&& other) noexcept
{
    if (this != &other)
    {
        delete[] vectorData_;

        vectorData_ = other.vectorData_;
        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;

        other.vectorData_ = nullptr;
        other.numBits_ = 0;
        other.numBytes_ = 0;
    }
    return *this;
}


uint32_t BooleanVector::getBitsCount() const
{
    return numBits_;
}

uint32_t BooleanVector::getBytesCount() const
{
    return numBytes_;
}

uint32_t BooleanVector::weight() const
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < numBits_; ++i)
    {
        if (getBit(i))
        {
            count++;
        }
    }
    return count;
}


void BooleanVector::ChangeVector()
{
for(uint32_t i=0;i<numBits_/2;i++)
{
    uint32_t j = numBits_ - 1 - i;

    bool leftbit = getBit(i);
    bool rightbit = getBit(j);

    setValue(i, rightbit);
    setValue(j, leftbit);

}
}

void BooleanVector::clear()
{
    for (uint32_t i = 0; i < numBytes_; ++i) 
    {
        setAll(false);
    }        clearUnusedBits();
}
uint32_t BooleanVector::countZeros() const
{
    return numBits_ - weight();
}

bool BooleanVector::isEmpty() const
{
    return numBits_ == 0;
}

bool BooleanVector::isAllZeros() const
{
    return weight() != 0;
}

uint32_t BooleanVector::countOnesInRange(const uint32_t startIndex, const uint32_t count) const
{
    assert((startIndex + count <= numBits_) && "Range is out of bounds.");
    uint32_t ones = 0;
    for (uint32_t i = startIndex; i < startIndex + count; ++i)
    {
        if (getBit(i))
        {
            ones++;
        }
    }
    return ones;
}

bool BooleanVector::getBit(const uint32_t bitIndex) const
{
    assert((bitIndex < numBits_) && "Index is out of range.");
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    return (vectorData_[byteIndex] & (1 << bitWithinByte)) != 0;
}

void BooleanVector::setValue(const uint32_t bitIndex, const bool newValue)
{
    assert((bitIndex < numBits_) && "Index is out of range.");
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    if (newValue)
        vectorData_[byteIndex] |= (1 << bitWithinByte);
    else
        vectorData_[byteIndex] &= ~(1 << bitWithinByte);
}

void BooleanVector::setRange(const uint32_t startIndex, const uint32_t count, const bool newValue)
{
    assert((startIndex + count <= numBits_) && "Range is out of vector bounds.");
    for (uint32_t i = startIndex; i < startIndex + count; ++i)
    {
        setValue(i, newValue);
    }
}

void BooleanVector::setAll(const bool newValue)
{
    uint8_t fillByte = newValue ? 0xFF : 0x00;
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        vectorData_[i] = fillByte;
    }
    clearUnusedBits();
}

void BooleanVector::invertAll()
{
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        vectorData_[i] = ~vectorData_[i];
    }
    clearUnusedBits();
}

void BooleanVector::invertBit(const uint32_t bitIndex)
{
    assert((bitIndex < numBits_) && "Index is out of range.");
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    vectorData_[byteIndex] ^= (1 << bitWithinByte);
    clearUnusedBits();
}

void BooleanVector::swap(BooleanVector& other) noexcept
{
    std::swap(vectorData_, other.vectorData_);
    std::swap(numBits_, other.numBits_);
    std::swap(numBytes_, other.numBytes_);
}

void BooleanVector::clearUnusedBits()
{
    uint32_t remainder = numBits_ % 8;
    if (remainder != 0 && numBytes_ > 0)
    {
        uint8_t mask = (1 << remainder) - 1;
        vectorData_[numBytes_ - 1] &= mask;
    }
}

bool BooleanVector::operator[](const uint32_t bitIndex) const
{
    return getBit(bitIndex);
}

BooleanVector::BitReference BooleanVector::operator[](const uint32_t bitIndex)
{
    assert((bitIndex < numBits_) && "Index is out of range.");
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    return BitReference(&vectorData_[byteIndex], bitWithinByte);
}


BooleanVector BooleanVector::operator~() const
{
    BooleanVector result(*this);
    result.invertAll();
    return result;
}

BooleanVector BooleanVector::operator&(const BooleanVector& other) const
{
    assert((numBits_ == other.numBits_) && "Vectors must have equal size.");
    BooleanVector result(numBits_);
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        result.vectorData_[i] = vectorData_[i] & other.vectorData_[i];
    }
    return result;
}

BooleanVector& BooleanVector::operator&=(const BooleanVector& other)
{
    assert((numBits_ == other.numBits_) && "Vectors must have equal size.");
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        vectorData_[i] &= other.vectorData_[i];
    }
    return *this;
}

BooleanVector BooleanVector::operator|(const BooleanVector& other) const
{
    assert((numBits_ == other.numBits_) && "Vectors must have equal size.");
    BooleanVector result(numBits_);
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        result.vectorData_[i] = vectorData_[i] | other.vectorData_[i];
    }
    return result;
}

BooleanVector& BooleanVector::operator|=(const BooleanVector& other)
{
    assert((numBits_ == other.numBits_) && "Vectors must have equal size.");
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        vectorData_[i] |= other.vectorData_[i];
    }
    return *this;
}

BooleanVector BooleanVector::operator^(const BooleanVector& other) const
{
    assert((numBits_ == other.numBits_) && "Vectors must have equal size.");
    BooleanVector result(numBits_);
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        result.vectorData_[i] = vectorData_[i] ^ other.vectorData_[i];
    }
    return result;
}

BooleanVector& BooleanVector::operator^=(const BooleanVector& other)
{
    assert((numBits_ == other.numBits_) && "Vectors must have equal size.");
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        vectorData_[i] ^= other.vectorData_[i];
    }
    return *this;
}



BooleanVector BooleanVector::operator>>(const uint32_t shiftCount) const
{
    BooleanVector result(numBits_, false);
    if (shiftCount >= numBits_)
    {
        return result;
    }

    for (uint32_t i = numBits_; i > shiftCount; --i)
    {
        uint32_t targetIndex = i - 1;
        if (getBit(targetIndex - shiftCount))
        {
            result.setValue(targetIndex, true);
        }
    }
    return result;
}

BooleanVector& BooleanVector::operator<<=(const uint32_t shiftCount)
{
    *this = *this << shiftCount;
    return *this;
}

BooleanVector BooleanVector::operator<<(const uint32_t shiftCount) const
{
    BooleanVector result(numBits_, false);
    if (shiftCount >= numBits_)
    {
        return result;
    }

    for (uint32_t i = 0; i < numBits_ - shiftCount; ++i)
    {
        if (getBit(i + shiftCount))
        {
            result.setValue(i, true);
        }
    }
    return result;
}

BooleanVector& BooleanVector::operator>>=(const uint32_t shiftCount)
{
    *this = *this >> shiftCount;
    return *this;
}

bool BooleanVector::operator==(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) return false;
    for (uint32_t i = 0; i < numBytes_; ++i)
    {
        if (vectorData_[i] != other.vectorData_[i]) return false;
    }
    return true;
}

bool BooleanVector::operator!=(const BooleanVector& other) const
{
    return !(*this == other);
}


BooleanVector::BitReference::BitReference(uint8_t* bytePtr, const uint32_t bitIndex)
    : bytePtr_(bytePtr), bitIndex_(bitIndex)
{
}

BooleanVector::BitReference::operator bool() const
{
    return (*bytePtr_ & (1 << bitIndex_)) != 0;
}

BooleanVector::BitReference& BooleanVector::BitReference::operator=(const bool newValue)
{
    if (newValue)
        *bytePtr_ |= (1 << bitIndex_);
    else
        *bytePtr_ &= ~(1 << bitIndex_);
    return *this;
}

BooleanVector::BitReference& BooleanVector::BitReference::operator=(const BitReference& rhs)
{
    return *this = static_cast<bool>(rhs);
}

BooleanVector::BitReference& BooleanVector::BitReference::operator&=(const bool val)
{
    bool current = *this;
    return *this = (current & val);
}

BooleanVector::BitReference& BooleanVector::BitReference::operator|=(const bool val)
{
    bool current = *this;
    return *this = (current | val);
}

BooleanVector::BitReference& BooleanVector::BitReference::operator^=(const bool val)
{
    bool current = *this;
    return *this = (current ^ val);
}

std::istream& operator>>(std::istream& inputStream, BooleanVector& booleanVector)
{
    std::string bitString;
    inputStream >> bitString;
    for (uint32_t i = 0; i < bitString.length(); ++i)
    {
        char c = bitString[i];
        assert((c == '0' || c == '1') && "Error: 0 and 1.");
    }

    booleanVector = BooleanVector(bitString.c_str());
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
