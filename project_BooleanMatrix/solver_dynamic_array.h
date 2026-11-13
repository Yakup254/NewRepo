#pragma once
#include <assert.h>
#include <algorithm>
#include <iostream>

template<typename ItemType>
class DynamicArray
{
public:
    class iterator;
    class const_iterator;

    void input();
    void output() const;

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
    bool insert(const_iterator pos, const ItemType& item);
    bool removeValue(const ItemType& item);
    void removeAll(const ItemType& item);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

private:
    void reserve(const int newCapacity);
    void shrinkToFitIfNeeded();

    ItemType* arrayData_ = nullptr;
    int arrayLength_ = 0;
    int arrayCapacity_ = 0;
};

template<typename ItemType>
class DynamicArray<ItemType>::iterator
{
public:
    iterator() = default;
    iterator(ItemType* arrayData, int elementIndex);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    iterator& operator++();
    iterator operator++(int);
    iterator operator+(int n) const;
    iterator operator-(int n) const;
    int operator-(const iterator& other) const;
    ItemType& operator*();
    ItemType* operator->();
    int getIndex() const;

private:
    ItemType* arrayData_ = nullptr;
    int elementIndex_ = 0;
};

template<typename ItemType>
class DynamicArray<ItemType>::const_iterator
{
public:
    const_iterator() = default;
    const_iterator(const ItemType* arrayData, int elementIndex);

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    const_iterator& operator++();
    const_iterator operator+(int n) const;
    const_iterator operator-(int n) const;
    int operator-(const const_iterator& other) const;
    const ItemType& operator*() const;
    const ItemType* operator->() const;
    int getIndex() const;

private:
    const ItemType* arrayData_ = nullptr;
    int elementIndex_ = 0;
};

template<typename ItemType>
std::ostream& operator<<(std::ostream& outputStream, const DynamicArray<ItemType>& arrayRef);
template<typename ItemType>
std::istream& operator>>(std::istream& inputStream, DynamicArray<ItemType>& arrayRef);


#include "solver_arrays.inl"
