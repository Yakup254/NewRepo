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
DynamicArray<ItemType>::~DynamicArray() 
{ 
    delete[] arrayData_; 
}

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
void DynamicArray<ItemType>::shrinkToFitIfNeeded()
{
    if (arrayLength_ < arrayCapacity_ / 4 && arrayCapacity_ > 8)
    {
        int newCapacity = arrayCapacity_ / 2;
        ItemType* newArrayData = new ItemType[newCapacity];
        for (int index = 0; index < arrayLength_; index++) { newArrayData[index] = std::move(arrayData_[index]); }
        delete[] arrayData_; arrayData_ = newArrayData; arrayCapacity_ = newCapacity;
    }
}

template<typename ItemType>
bool DynamicArray<ItemType>::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int index = 0; index < arrayLength_; index++) 
    { 
        if (arrayData_[index] != other.arrayData_[index])
        return false; 
    }
    return true;
}

template<typename ItemType> bool DynamicArray<ItemType>::operator!=(const DynamicArray& other) const 
{ 
    return !(*this == other); 
}

template<typename ItemType>
bool DynamicArray<ItemType>::insertAt(const int index, const ItemType& item)
{
    if (index < 0 || index > arrayLength_) return false;
    if (arrayLength_ == arrayCapacity_)
    {
        if (arrayCapacity_ == 0) reserve(4);
        else reserve(arrayCapacity_ * 2);
    }
    for (int i = arrayLength_; i > index; i--) 
    { 
        arrayData_[i] = std::move(arrayData_[i - 1]);
    }
    arrayData_[index] = item; arrayLength_++; 
    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeAt(const int index)
{
    if (index < 0 || index >= arrayLength_) return false;
    for (int i = index; i < arrayLength_ - 1; i++) { arrayData_[i] = std::move(arrayData_[i + 1]); }
    arrayLength_--; shrinkToFitIfNeeded(); return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeValue(const ItemType& item)
{
    int index = find(item);
    if (index == -1)
    {
        return false;
    }
    return removeAt(index);
}
template<typename ItemType>
void DynamicArray<ItemType>::removeAll(const ItemType& item)
{
    int writeIndex = 0;
    for (int readIndex = 0; readIndex < arrayLength_; readIndex++)
    {
        if (arrayData_[readIndex] != item)
        {
            if (writeIndex != readIndex)
            {
                arrayData_[writeIndex] = std::move(arrayData_[readIndex]);
            }
            writeIndex++;
        }
    }
    arrayLength_ = writeIndex;
    shrinkToFitIfNeeded();
}
template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const DynamicArray& other)
{
    for (int index = 0; index < other.arrayLength_; index++)
    {
        *this += other.arrayData_[index];
    }
    return *this;
}

template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const DynamicArray& other) const
{
    DynamicArray result(*this);
    result += other;
    return result;
}

template<typename ItemType>
int DynamicArray<ItemType>::find(const ItemType& item) const
{
    for (int index = 0; index < arrayLength_; index++)
    {
        if (arrayData_[index] == item)
        {
            return index;
        }
    }
    return -1;
}
template<typename ItemType>
ItemType DynamicArray<ItemType>::findMin() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    ItemType minValue = arrayData_[0];
    for (int index = 1; index < arrayLength_; index++)
    {
        if (arrayData_[index] < minValue)
        {
            minValue = arrayData_[index];
        }
    }
    return minValue;
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::findMax() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    ItemType maxValue = arrayData_[0];
    for (int index = 1; index < arrayLength_; index++)
    {
        if (arrayData_[index] > maxValue)
        {
            maxValue = arrayData_[index];
        }
    }
    return maxValue;
}
template<typename ItemType> void DynamicArray<ItemType>::sort() 
{ 
    std::sort(arrayData_, arrayData_ + arrayLength_); 
}

template<typename ItemType>
std::ostream& operator<<(std::ostream& outputStream, const DynamicArray<ItemType>& arrayRef)
{
    outputStream << "[";
    for (int index = 0; index < arrayRef.getLength(); index++) 
    {
        outputStream << arrayRef[index]; 
        if (index < arrayRef.getLength() - 1)
            outputStream << ", "; 
    }
    outputStream << "]"; return outputStream;
}
