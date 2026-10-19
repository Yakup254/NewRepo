#include "solver_dynamic_array.h"

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray() : arrayData_(nullptr), arrayLength_(0), arrayCapacity_(0) {}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const ItemType* const arrayData, const int arrayLength) : arrayLength_(arrayLength), arrayCapacity_(arrayLength)
{
    if (arrayCapacity_ > 0)
    {
        arrayData_ = new ItemType[arrayCapacity_];
        for (int index = 0; index < arrayLength_; index++)
        {
            arrayData_[index] = arrayData[index];
        }
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const DynamicArray& other) : arrayLength_(other.arrayLength_), arrayCapacity_(other.arrayCapacity_)
{
    if (arrayCapacity_ > 0)
    {
        arrayData_ = new ItemType[arrayCapacity_];
        for (int index = 0; index < arrayLength_; index++)
        {
            arrayData_[index] = other.arrayData_[index];
        }
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(DynamicArray&& other) noexcept
{
    arrayLength_ = other.arrayLength_; other.arrayLength_ = 0;
    arrayCapacity_ = other.arrayCapacity_; other.arrayCapacity_ = 0;
    arrayData_ = other.arrayData_; other.arrayData_ = nullptr;
}

template<typename ItemType>
DynamicArray<ItemType>::~DynamicArray() { delete[] arrayData_; }

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray& other)
{
    if (this != &other) { DynamicArray copy(other); swap(copy); }
    return *this;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(DynamicArray&& other) noexcept
{
    if (this != &other)
    {
        delete[] arrayData_;
        arrayLength_ = other.arrayLength_; other.arrayLength_ = 0;
        arrayCapacity_ = other.arrayCapacity_; other.arrayCapacity_ = 0;
        arrayData_ = other.arrayData_; other.arrayData_ = nullptr;
    }
    return *this;
}

template<typename ItemType> int DynamicArray<ItemType>::getLength() const { return arrayLength_; }
template<typename ItemType> int DynamicArray<ItemType>::getCapacity() const { return arrayCapacity_; }

template<typename ItemType>
void DynamicArray<ItemType>::reserve(const int newCapacity)
{
    if (newCapacity <= arrayCapacity_) return;
    ItemType* newArrayData = new ItemType[newCapacity];
    for (int index = 0; index < arrayLength_; index++)
    {
        newArrayData[index] = std::move(arrayData_[index]);
    }
    delete[] arrayData_;
    arrayData_ = newArrayData;
    arrayCapacity_ = newCapacity;
}

template<typename ItemType>
ItemType& DynamicArray<ItemType>::operator[](const int index)
{
    assert((index >= 0 && index < arrayLength_) && "Index out of range.");
    return arrayData_[index];
}

template<typename ItemType>
const ItemType& DynamicArray<ItemType>::operator[](const int index) const
{
    assert((index >= 0 && index < arrayLength_) && "Index out of range.");
    return arrayData_[index];
}

template<typename ItemType>
void DynamicArray<ItemType>::swap(DynamicArray& other) noexcept
{
    std::swap(arrayLength_, other.arrayLength_);
    std::swap(arrayCapacity_, other.arrayCapacity_);
    std::swap(arrayData_, other.arrayData_);
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const ItemType& item)
{
    if (arrayLength_ == arrayCapacity_)
    {
        if (arrayCapacity_ == 0) {
            reserve(4);
        }
        else {
            reserve(arrayCapacity_ * 2);
        }
    }
    arrayData_[arrayLength_] = item;
    arrayLength_++;
    return *this;
}

template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const ItemType& item) const
{
    DynamicArray result(*this); result += item; return result;
}

template<typename ItemType>
std::ostream& operator<<(std::ostream& outputStream, const DynamicArray<ItemType>& arrayRef)
{
    outputStream << "[";
    for (int index = 0; index < arrayRef.getLength(); index++)
    {
        outputStream << arrayRef[index];
        if (index < arrayRef.getLength() - 1) outputStream << ", ";
    }
    outputStream << "]";
    return outputStream;
}
