#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>

template<typename ItemType>
class LinkedList
{
public:
    class ListNode;

    LinkedList() = default;
    LinkedList(const ItemType* arrayData, const uint32_t arrayLength);
    LinkedList(const LinkedList& other);
    ~LinkedList();

    LinkedList& operator=(const LinkedList& other);

    uint32_t getListSize() const;
    void swap(LinkedList& other) noexcept;
    void input();
    void output() const;

    ListNode* getHead() const;
    ListNode* getTail() const;

    ListNode* find(const ItemType& key) const;

    void addToHead(const ItemType& data);
    void addToTail(const ItemType& data);
    void insertAt(const uint32_t index, const ItemType& data);
    void insertAfterKey(const ItemType& key, const ItemType& data);

    void removeHead();
    void removeTail();
    void removeAt(const uint32_t index);
    bool removeByKey(const ItemType& key);

    ItemType& operator[](const uint32_t index);
    const ItemType& operator[](const uint32_t index) const;

    bool operator==(const LinkedList& other) const;
    bool operator!=(const LinkedList& other) const;

private:
    void clearInternal();

    ListNode* head_ = nullptr;
    ListNode* tail_ = nullptr;
    uint32_t size_ = 0;
};

template<typename ItemType>
class LinkedList<ItemType>::ListNode
{
public:
    ListNode() = default;
    ListNode(const ItemType& data, ListNode* const next = nullptr, ListNode* const prev = nullptr);
    ~ListNode() = default;

    ItemType& getDataRef();
    ItemType getData() const;
    void setData(const ItemType& data);

    ListNode* getLinkToNext() const;
    void setLinkToNext(ListNode* const next);

    ListNode* getLinkToPrev() const;
    void setLinkToPrev(ListNode* const prev);

private:
    ItemType data_ = ItemType();
    ListNode* next_ = nullptr;
    ListNode* prev_ = nullptr;
};

template<typename ItemType>
std::ostream& operator<<(std::ostream& outputStream, const LinkedList<ItemType>& list);

template<typename ItemType>
std::istream& operator>>(std::istream& inputStream, LinkedList<ItemType>& list);

#include "LinkedList.inl"
