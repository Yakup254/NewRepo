#pragma once
#include <assert.h>
#include <algorithm>
#include <iostream>

class IntDynamicArray
{
public:
    class iterator;
    class const_iterator;

    void input();
    void output() const;

    IntDynamicArray();
    IntDynamicArray(const int* const arrayData, const int arrayLength);
    IntDynamicArray(const IntDynamicArray& other);
    IntDynamicArray(IntDynamicArray&& other) noexcept;
    ~IntDynamicArray();

    IntDynamicArray& operator=(const IntDynamicArray& other);
    IntDynamicArray& operator=(IntDynamicArray&& other) noexcept;

    int getLength() const;
    int getCapacity() const;

    int& operator[](const int index);
    const int& operator[](const int index) const;
    void swap(IntDynamicArray& other) noexcept;

    bool operator==(const IntDynamicArray& other) const;
    bool operator!=(const IntDynamicArray& other) const;

    IntDynamicArray& operator+=(const int item);
    IntDynamicArray operator+(const int item) const;
    IntDynamicArray& operator+=(const IntDynamicArray& other);
    IntDynamicArray operator+(const IntDynamicArray& other) const;

    int find(const int item) const;
    int findMin() const;
    int findMax() const;
    void sort();

    bool insertAt(const int index, const int item);
    bool removeAt(const int index);
    bool insert(const_iterator pos, const int item);
    bool removeValue(const int item);
    void removeAll(const int item);

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

    int* arrayData_ = nullptr;
    int arrayLength_ = 0;
    int arrayCapacity_ = 0;
};
class IntDynamicArray::iterator
{
public:
    iterator() = default;
    iterator(int* arrayData, int elementIndex);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    iterator& operator++();
    iterator operator++(int);
    iterator operator+(int n) const;
    iterator operator-(int n) const;
    int operator-(const iterator& other) const;
    int& operator*();
    int* operator->();
    int getIndex() const;

private:
    int* arrayData_ = nullptr;
    int elementIndex_ = 0;
};

class IntDynamicArray::const_iterator
{
public:
    const_iterator() = default;
    const_iterator(const int* arrayData, int elementIndex);

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    const_iterator& operator++();
    const_iterator operator+(int n) const;
    const_iterator operator-(int n) const;
    int operator-(const const_iterator& other) const;
    const int& operator*() const;
    const int* operator->() const;
    int getIndex() const;

private:
    const int* arrayData_ = nullptr;
    int elementIndex_ = 0;
};

std::ostream& operator<<(std::ostream& outputStream, const IntDynamicArray& arrayRef);
