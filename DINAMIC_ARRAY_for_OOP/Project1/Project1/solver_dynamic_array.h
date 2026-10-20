#pragma once
#include <assert.h>
#include <algorithm>
#include <iostream>

template<typename ItemType>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(const ItemType* const arrayData, const int arrayLength);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    int getLength() const;
    int getCapacity() const;

    ItemType& operator[](const int index);
    const ItemType& operator[](const int index) const;
    void swap(DynamicArray& other) noexcept;

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    DynamicArray& operator+=(const ItemType& item);
    DynamicArray operator+(const ItemType& item) const;
    DynamicArray& operator+=(const DynamicArray& other);
    DynamicArray operator+(const DynamicArray& other) const;

    int find(const ItemType& item) const;
    ItemType findMin() const;
    ItemType findMax() const;
    void sort();

    bool insertAt(const int index, const ItemType& item);
    bool removeAt(const int index);
    bool removeValue(const ItemType& item);
    void removeAll(const ItemType& item);



private:
    void reserve(const int newCapacity);
    void shrinkToFitIfNeeded();

    ItemType* arrayData_ = nullptr;
    int arrayLength_ = 0;
    int arrayCapacity_ = 0;
};

template<typename ItemType>
std::ostream& operator<<(std::ostream& outputStream, const DynamicArray<ItemType>& arrayRef);

#include "solver_arrays.inl"
