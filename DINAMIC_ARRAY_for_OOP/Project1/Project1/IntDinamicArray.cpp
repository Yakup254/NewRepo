#include "IntDinamicArray.h"

IntDynamicArray::IntDynamicArray() : arrayData_(nullptr), arrayLength_(0), arrayCapacity_(0)
{
    std::cout << "IntDynamicArray::IntDynamicArray()" << std::endl;
}

IntDynamicArray::IntDynamicArray(const int* const arrayData, const int arrayLength)
    : arrayLength_(arrayLength), arrayCapacity_(arrayLength)
{
    if (arrayCapacity_ > 0)
    {
        arrayData_ = new int[arrayCapacity_];
        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = arrayData[index];
    }
}

IntDynamicArray::IntDynamicArray(const IntDynamicArray& other)
    : arrayLength_(other.arrayLength_), arrayCapacity_(other.arrayCapacity_)
{
    if (arrayCapacity_ > 0)
    {
        arrayData_ = new int[arrayCapacity_];
        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = other.arrayData_[index];
    }
}

IntDynamicArray::IntDynamicArray(IntDynamicArray&& other) noexcept
{

    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = 0;

    arrayCapacity_ = other.arrayCapacity_;
    other.arrayCapacity_ = 0;

    arrayData_ = other.arrayData_;
    other.arrayData_ = nullptr;
}

IntDynamicArray::~IntDynamicArray() { delete[] arrayData_; }

IntDynamicArray& IntDynamicArray::operator=(const IntDynamicArray& other)
{
    if (this != &other)
    {
        IntDynamicArray copy(other);
        swap(copy);
    }
    return *this;
}

IntDynamicArray& IntDynamicArray::operator=(IntDynamicArray&& other) noexcept
{
    if (this != &other)
    {
        delete[] arrayData_;
        arrayLength_ = other.arrayLength_;
        other.arrayLength_ = 0;
        arrayCapacity_ = other.arrayCapacity_;
        other.arrayCapacity_ = 0;
        arrayData_ = other.arrayData_;
        other.arrayData_ = nullptr;
    }
    return *this;
}

int IntDynamicArray::getLength() const { return arrayLength_; }
int IntDynamicArray::getCapacity() const { return arrayCapacity_; }

void IntDynamicArray::reserve(const int newCapacity)
{
    if (newCapacity <= arrayCapacity_) return;
    int* newArrayData = new int[newCapacity];

    for (int index = 0; index < arrayLength_; index++)
    {
        newArrayData[index] = arrayData_[index];
    }

    delete[] arrayData_;
    arrayData_ = newArrayData;
    arrayCapacity_ = newCapacity;
}

int& IntDynamicArray::operator[](const int index)
{
    assert((index >= 0 && index < arrayLength_) && "Index out of range.");
    return arrayData_[index];
}

const int& IntDynamicArray::operator[](const int index) const
{
    assert((index >= 0 && index < arrayLength_) && "Index out of range.");
    return arrayData_[index];
}

void IntDynamicArray::swap(IntDynamicArray& other) noexcept
{
    std::swap(arrayLength_, other.arrayLength_);
    std::swap(arrayCapacity_, other.arrayCapacity_);
    std::swap(arrayData_, other.arrayData_);
}
IntDynamicArray& IntDynamicArray::operator+=(const int item)
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

IntDynamicArray IntDynamicArray::operator+(const int item) const
{
    IntDynamicArray result(*this); result += item; return result;
}

void IntDynamicArray::shrinkToFitIfNeeded()
{
    if (arrayLength_ < arrayCapacity_ / 4 && arrayCapacity_ > 8)
    {
        int newCapacity = arrayCapacity_ / 2;
        int* newArrayData = new int[newCapacity];

        for (int index = 0; index < arrayLength_; index++)
        {
            newArrayData[index] = arrayData_[index];
        }

        delete[] arrayData_;
        arrayData_ = newArrayData;
        arrayCapacity_ = newCapacity;
    }
}
bool IntDynamicArray::operator==(const IntDynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int index = 0; index < arrayLength_; index++)
    {
        if (arrayData_[index] != other.arrayData_[index])
            return false;
    }
    return true;
}

bool IntDynamicArray::operator!=(const IntDynamicArray& other) const
{
    return !(*this == other);
}

bool IntDynamicArray::insertAt(const int index, const int item)
{
    if (index < 0 || index > arrayLength_) return false;
    if (arrayLength_ == arrayCapacity_)
    {
        if (arrayCapacity_ == 0) reserve(4);
        else reserve(arrayCapacity_ * 2);
    }
    for (int i = arrayLength_; i > index; i--)
    {
        arrayData_[i] = arrayData_[i - 1];;
    }
    arrayData_[index] = item; arrayLength_++;
    return true;
}

bool IntDynamicArray::removeAt(const int index)
{
    if (index < 0 || index >= arrayLength_) return false;
    for (int i = index; i < arrayLength_ - 1; i++)
    {
        arrayData_[i] = arrayData_[i + 1];
    }
    arrayLength_--;
    shrinkToFitIfNeeded(); return true;
}

bool IntDynamicArray::removeValue(const int item)
{
    int index = find(item);
    if (index == -1) return false;
    return removeAt(index);
}

void IntDynamicArray::removeAll(const int item)
{
    int writeIndex = 0;
    for (int readIndex = 0; readIndex < arrayLength_; readIndex++)
    {
        if (arrayData_[readIndex] != item)
        {
            if (writeIndex != readIndex) { arrayData_[writeIndex] = arrayData_[readIndex]; }
            writeIndex++;
        }
    }
    arrayLength_ = writeIndex; shrinkToFitIfNeeded();
}

IntDynamicArray& IntDynamicArray::operator+=(const IntDynamicArray& other)
{
    for (int index = 0; index < other.arrayLength_; index++)
    {
        *this += other.arrayData_[index];
    }
    return *this;
}

IntDynamicArray IntDynamicArray::operator+(const IntDynamicArray& other) const
{
    IntDynamicArray result(*this);
    result += other;
    return result;
}

int IntDynamicArray::find(const int item) const
{
    for (int index = 0; index < arrayLength_; index++)
    {
        if (arrayData_[index] == item) return index;
    }
    return -1;
}

int IntDynamicArray::findMin() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    int minValue = arrayData_[0];
    for (int index = 1; index < arrayLength_; index++)
    {
        if (arrayData_[index] < minValue)
            minValue = arrayData_[index];
    }
    return minValue;
}

int IntDynamicArray::findMax() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    int maxValue = arrayData_[0];
    for (int index = 1; index < arrayLength_; index++)
    {
        if (arrayData_[index] > maxValue)
            maxValue = arrayData_[index];
    }
    return maxValue;
}

void IntDynamicArray::sort()
{
    int n = arrayLength_;
    if (n <= 1) return;

    int gapCount = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        gapCount++;
    }

    int* gaps = new int[gapCount];
    int idx = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        gaps[idx++] = gap;
    }
    int t = gapCount - 1;

    for (int i = 0; i <= t; ++i) {
        int s = gaps[i];
        for (int b = 0; b < s; ++b) {
            for (int j = b + s; j < n; j += s) {
                int x = arrayData_[j];
                int k = j - s;
                while (k >= 0 && arrayData_[k] > x) {
                    arrayData_[k + s] = arrayData_[k];
                    k = k - s;
                }
                arrayData_[k + s] = x;
            }
        }
    }

    delete[] gaps;
}


IntDynamicArray::iterator IntDynamicArray::begin()
{
    return iterator(arrayData_, 0);
}

IntDynamicArray::iterator IntDynamicArray::end()
{
    return iterator(arrayData_, arrayLength_);
}

IntDynamicArray::const_iterator IntDynamicArray::begin() const
{
    return const_iterator(arrayData_, 0);
}

IntDynamicArray::const_iterator IntDynamicArray::end() const
{
    return const_iterator(arrayData_, arrayLength_);
}

IntDynamicArray::const_iterator IntDynamicArray::cbegin() const
{
    return const_iterator(arrayData_, 0);
}

IntDynamicArray::const_iterator IntDynamicArray::cend() const
{
    return const_iterator(arrayData_, arrayLength_);
}

IntDynamicArray::iterator::iterator(int* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{
}

bool IntDynamicArray::iterator::operator==(const iterator& other) const
{
    return elementIndex_ == other.elementIndex_ && arrayData_ == other.arrayData_;
}

bool IntDynamicArray::iterator::operator!=(const iterator& other) const
{
    return elementIndex_ != other.elementIndex_ || arrayData_ != other.arrayData_;
}

IntDynamicArray::iterator& IntDynamicArray::iterator::operator++()
{
    elementIndex_++;
    return *this;
}

IntDynamicArray::iterator IntDynamicArray::iterator::operator++(int)
{
    iterator temp(*this);
    elementIndex_++;
    return temp;
}

IntDynamicArray::iterator IntDynamicArray::iterator::operator+(int n) const
{
    return iterator(arrayData_, elementIndex_ + n);
}

IntDynamicArray::iterator IntDynamicArray::iterator::operator-(int n) const
{
    return iterator(arrayData_, elementIndex_ - n);
}

int IntDynamicArray::iterator::operator-(const iterator& other) const
{
    return elementIndex_ - other.elementIndex_;
}

int& IntDynamicArray::iterator::operator*()
{
    return arrayData_[elementIndex_];
}

int* IntDynamicArray::iterator::operator->()
{
    return &arrayData_[elementIndex_];
}

int IntDynamicArray::iterator::getIndex() const
{
    return elementIndex_;
}

IntDynamicArray::const_iterator::const_iterator(const int* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{
}

bool IntDynamicArray::const_iterator::operator==(const const_iterator& other) const
{
    return elementIndex_ == other.elementIndex_ && arrayData_ == other.arrayData_;
}

bool IntDynamicArray::const_iterator::operator!=(const const_iterator& other) const
{
    return elementIndex_ != other.elementIndex_ || arrayData_ != other.arrayData_;
}

IntDynamicArray::const_iterator& IntDynamicArray::const_iterator::operator++()
{
    elementIndex_++;
    return *this;
}

IntDynamicArray::const_iterator IntDynamicArray::const_iterator::operator+(int n) const
{
    return const_iterator(arrayData_, elementIndex_ + n);
}

IntDynamicArray::const_iterator IntDynamicArray::const_iterator::operator-(int n) const
{
    return const_iterator(arrayData_, elementIndex_ - n);
}

int IntDynamicArray::const_iterator::operator-(const const_iterator& other) const
{
    return elementIndex_ - other.elementIndex_;
}

const int& IntDynamicArray::const_iterator::operator*() const
{
    return arrayData_[elementIndex_];
}

const int* IntDynamicArray::const_iterator::operator->() const
{
    return &arrayData_[elementIndex_];
}
int IntDynamicArray::const_iterator::getIndex() const
{
    return elementIndex_;
}

IntDynamicArray::iterator IntDynamicArray::erase(const_iterator pos)
{
    int index = pos.getIndex();
    removeAt(index);
    return iterator(arrayData_, index);
}

IntDynamicArray::iterator IntDynamicArray::erase(const_iterator first, const_iterator last)
{
    int firstIdx = first.getIndex();
    int lastIdx = last.getIndex();
    int numToRemove = lastIdx - firstIdx;
    for (int i = firstIdx; i < arrayLength_ - numToRemove; i++)
    {
        arrayData_[i] = arrayData_[i + numToRemove];
    }
    arrayLength_ -= numToRemove;
    shrinkToFitIfNeeded();
    return iterator(arrayData_, firstIdx);
}

void IntDynamicArray::input()
{
    int count = 0;
    std::cout << "input for add numbers: ";
    if (std::cin >> count && count > 0)
    {
        for (int i = 0; i < count; ++i)
        {
            int value = 0;
            std::cout << "Element (" << i << "): ";
            std::cin >> value;
            *this += value;
        }
    }
}

void IntDynamicArray::output() const
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
bool IntDynamicArray::insert(const_iterator pos, const int item)
{
    int index = pos.getIndex(); 
    return insertAt(index, item);
}



std::ostream& operator<<(std::ostream& outputStream, const IntDynamicArray& arrayRef)
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
