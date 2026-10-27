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
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::begin()
{
    return iterator(arrayData_, 0);
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::end()
{
    return iterator(arrayData_, arrayLength_);
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::begin() const
{
    return const_iterator(arrayData_, 0);
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::end() const
{
    return const_iterator(arrayData_, arrayLength_);
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::cbegin() const
{
    return const_iterator(arrayData_, 0);
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::cend() const
{
    return const_iterator(arrayData_, arrayLength_);
}


template<typename ItemType>
DynamicArray<ItemType>::iterator::iterator(ItemType* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{
}

template<typename ItemType>
bool DynamicArray<ItemType>::iterator::operator==(const iterator& other) const
{
    return elementIndex_ == other.elementIndex_ && arrayData_ == other.arrayData_;
}

template<typename ItemType>
bool DynamicArray<ItemType>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator& DynamicArray<ItemType>::iterator::operator++()
{
    elementIndex_++;
    return *this;
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::iterator::operator++(int)
{
    iterator temp = *this;
    elementIndex_++;
    return temp;
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::iterator::operator+(int n) const
{
    return iterator(arrayData_, elementIndex_ + n);
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::iterator::operator-(int n) const
{
    return iterator(arrayData_, elementIndex_ - n);
}

template<typename ItemType>
int DynamicArray<ItemType>::iterator::operator-(const iterator& other) const
{
    return elementIndex_ - other.elementIndex_;
}

template<typename ItemType>
ItemType& DynamicArray<ItemType>::iterator::operator*()
{
    return arrayData_[elementIndex_];
}

template<typename ItemType>
ItemType* DynamicArray<ItemType>::iterator::operator->()
{
    return &arrayData_[elementIndex_];
}

template<typename ItemType>
int DynamicArray<ItemType>::iterator::getIndex() const
{
    return elementIndex_;
}

template<typename ItemType>
DynamicArray<ItemType>::const_iterator::const_iterator(const ItemType* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{
}

template<typename ItemType>
bool DynamicArray<ItemType>::const_iterator::operator==(const const_iterator& other) const
{
    return elementIndex_ == other.elementIndex_ && arrayData_ == other.arrayData_;
}

template<typename ItemType>
bool DynamicArray<ItemType>::const_iterator::operator!=(const const_iterator& other) const
{
    return !(*this == other);
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator& DynamicArray<ItemType>::const_iterator::operator++()
{
    elementIndex_++;
    return *this;
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::const_iterator::operator+(int n) const
{
    return const_iterator(arrayData_, elementIndex_ + n);
}

template<typename ItemType>
typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::const_iterator::operator-(int n) const
{
    return const_iterator(arrayData_, elementIndex_ - n);
}

template<typename ItemType>
int DynamicArray<ItemType>::const_iterator::operator-(const const_iterator& other) const
{
    return elementIndex_ - other.elementIndex_;
}

template<typename ItemType>
const ItemType& DynamicArray<ItemType>::const_iterator::operator*() const
{
    return arrayData_[elementIndex_];
}

template<typename ItemType>
const ItemType* DynamicArray<ItemType>::const_iterator::operator->() const
{
    return &arrayData_[elementIndex_];
}

template<typename ItemType>
int DynamicArray<ItemType>::const_iterator::getIndex() const
{
    return elementIndex_;
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::erase(const_iterator pos)
{
    int index = pos.getIndex();
    removeAt(index);
    return iterator(arrayData_, index);
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::erase(const_iterator first, const_iterator last)
{
    int firstIdx = first.getIndex();
    int lastIdx = last.getIndex();
    int numToRemove = lastIdx - firstIdx;

    for (int i = firstIdx; i < arrayLength_ - numToRemove; i++)
    {
        arrayData_[i] = std::move(arrayData_[i + numToRemove]);
    }

    arrayLength_ -= numToRemove;
    shrinkToFitIfNeeded();
    return iterator(arrayData_, firstIdx);
}

template<typename ItemType>
void DynamicArray<ItemType>::input()
{
    int count = 0;
    std::cout << "input for add numbers: ";
    if (std::cin >> count && count > 0)
    {
        for (int i = 0; i < count; ++i)
        {
            ItemType value;
            std::cout << "Element (" << i << "): ";
            std::cin >> value;
            *this += value;
        }
    }
}

template<typename ItemType>
void DynamicArray<ItemType>::output() const
{
    std::cout << "[";
    for (int index = 0; index < arrayLength_; index++)
    {
        std::cout << arrayData_[index];
        if (index < arrayLength_ - 1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template<typename ItemType>
bool DynamicArray<ItemType>::insert(const_iterator pos, const ItemType& item)
{
    int index = pos.getIndex();
    return insertAt(index, item); 
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
