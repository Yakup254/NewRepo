#pragma once

template<typename ItemType>
LinkedList<ItemType>::LinkedList(const ItemType* arrayData, const uint32_t arrayLength)
{
    assert((arrayData != nullptr || arrayLength == 0) && "Null array pointer.");
    for (uint32_t i = 0; i < arrayLength; ++i)
    {
        addToTail(arrayData[i]);
    }
}

template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList& other)
{
    ListNode* current = other.head_;
    while (current != nullptr)
    {
        addToTail(current->getData());
        current = current->getLinkToNext();
    }
}

template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clearInternal();
}

template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList& other)
{
    if (this != &other)
    {
        LinkedList copy(other);
        swap(copy);
    }
    return *this;
}

template<typename ItemType>
void LinkedList<ItemType>::clearInternal()
{
    while (head_ != nullptr)
    {
        removeHead();
    }
}

template<typename ItemType>
uint32_t LinkedList<ItemType>::getListSize() const
{
    return size_;
}

template<typename ItemType>
void LinkedList<ItemType>::swap(LinkedList& other) noexcept
{
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

template<typename ItemType>
void LinkedList<ItemType>::input()
{
    uint32_t count = 0;
    std::cout << "Enter number of elements: ";
    if (std::cin >> count)
    {
        clear();
        for (uint32_t i = 0; i < count; ++i)
        {
            ItemType value;
            std::cout << "Element (" << i << "): ";
            std::cin >> value;
            addToTail(value);
        }
    }
}

template<typename ItemType>
void LinkedList<ItemType>::output() const
{
    std::cout << "[";
    ListNode* current = head_;
    while (current != nullptr)
    {
        std::cout << current->getData();
        if (current->getLinkToNext() != nullptr)
        {
            std::cout << ", ";
        }
        current = current->getLinkToNext();
    }
    std::cout << "]" << std::endl;
}



template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::getHead() const
{
    return head_;
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::getTail() const
{
    return tail_;
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::find(const ItemType& key) const
{
    ListNode* current = head_;
    while (current != nullptr)
    {
        if (current->getData() == key)
        {
            return current;
        }
        current = current->getLinkToNext();
    }
    return nullptr;
}

template<typename ItemType>
void LinkedList<ItemType>::addToHead(const ItemType& data)
{
    ListNode* newNode = new ListNode(data, head_, nullptr);
    if (head_ != nullptr)
    {
        head_->setLinkToPrev(newNode);
    }
    head_ = newNode;
    if (tail_ == nullptr)
    {
        tail_ = newNode;
    }
    ++size_;
}

template<typename ItemType>
void LinkedList<ItemType>::addToTail(const ItemType& data)
{
    ListNode* newNode = new ListNode(data, nullptr, tail_);
    if (tail_ != nullptr)
    {
        tail_->setLinkToNext(newNode);
    }
    tail_ = newNode;
    if (head_ == nullptr)
    {
        head_ = newNode;
    }
    ++size_;
}

template<typename ItemType>
void LinkedList<ItemType>::insertAt(const uint32_t index, const ItemType& data)
{
    assert(index <= size_ && "Index is out of range.");
    if (index == 0)
    {
        addToHead(data);
        return;
    }
    if (index == size_)
    {
        addToTail(data);
        return;
    }

    ListNode* current = head_;
    for (uint32_t i = 0; i < index; ++i)
    {
        current = current->getLinkToNext();
    }

    ListNode* prevNode = current->getLinkToPrev();
    ListNode* newNode = new ListNode(data, current, prevNode);
    prevNode->setLinkToNext(newNode);
    current->setLinkToPrev(newNode);
    ++size_;
}

template<typename ItemType>
void LinkedList<ItemType>::insertAfterKey(const ItemType& key, const ItemType& data)
{
    ListNode* target = find(key);
    if (target == nullptr)
    {
        return;
    }
    if (target == tail_)
    {
        addToTail(data);
        return;
    }

    ListNode* nextNode = target->getLinkToNext();
    ListNode* newNode = new ListNode(data, nextNode, target);
    target->setLinkToNext(newNode);
    nextNode->setLinkToPrev(newNode);
    ++size_;
}

template<typename ItemType>
void LinkedList<ItemType>::removeHead()
{
    if (head_ == nullptr)
    {
        return;
    }
    ListNode* temp = head_;
    head_ = head_->getLinkToNext();
    if (head_ != nullptr)
    {
        head_->setLinkToPrev(nullptr);
    }
    else
    {
        tail_ = nullptr;
    }
    delete temp;
    --size_;
}

template<typename ItemType>
void LinkedList<ItemType>::removeTail()
{
    if (tail_ == nullptr)
    {
        return;
    }
    ListNode* temp = tail_;
    tail_ = tail_->getLinkToPrev();
    if (tail_ != nullptr)
    {
        tail_->setLinkToNext(nullptr);
    }
    else
    {
        head_ = nullptr;
    }
    delete temp;
    --size_;
}

template<typename ItemType>
void LinkedList<ItemType>::removeAt(const uint32_t index)
{
    assert(index < size_ && "Index is out of range.");
    if (index == 0)
    {
        removeHead();
        return;
    }
    if (index == size_ - 1)
    {
        removeTail();
        return;
    }

    ListNode* current = head_;
    for (uint32_t i = 0; i < index; ++i)
    {
        current = current->getLinkToNext();
    }

    ListNode* prevNode = current->getLinkToPrev();
    ListNode* nextNode = current->getLinkToNext();
    prevNode->setLinkToNext(nextNode);
    nextNode->setLinkToPrev(prevNode);
    delete current;
    --size_;
}

template<typename ItemType>
bool LinkedList<ItemType>::removeByKey(const ItemType& key)
{
    ListNode* target = find(key);
    if (target == nullptr)
    {
        return false;
    }
    if (target == head_)
    {
        removeHead();
        return true;
    }
    if (target == tail_)
    {
        removeTail();
        return true;
    }

    ListNode* prevNode = target->getLinkToPrev();
    ListNode* nextNode = target->getLinkToNext();
    prevNode->setLinkToNext(nextNode);
    nextNode->setLinkToPrev(prevNode);
    delete target;
    --size_;
    return true;
}

template<typename ItemType>
ItemType& LinkedList<ItemType>::operator[](const uint32_t index)
{
    assert(index < size_ && "Index is out of range.");
    ListNode* current = head_;
    for (uint32_t i = 0; i < index; ++i)
    {
        current = current->getLinkToNext();
    }
    return current->getDataRef();
}

template<typename ItemType>
const ItemType& LinkedList<ItemType>::operator[](const uint32_t index) const
{
    assert(index < size_ && "Index is out of range.");
    ListNode* current = head_;
    for (uint32_t i = 0; i < index; ++i)
    {
        current = current->getLinkToNext();
    }
    return current->getData();
}

template<typename ItemType>
bool LinkedList<ItemType>::operator==(const LinkedList& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    ListNode* left = head_;
    ListNode* right = other.head_;
    while (left != nullptr)
    {
        if (left->getData() != right->getData())
        {
            return false;
        }
        left = left->getLinkToNext();
        right = right->getLinkToNext();
    }
    return true;
}

template<typename ItemType>
bool LinkedList<ItemType>::operator!=(const LinkedList& other) const
{
    return !(*this == other);
}


template<typename ItemType>
LinkedList<ItemType>::ListNode::ListNode(const ItemType& data, ListNode* const next, ListNode* const prev)
    : data_(data), next_(next), prev_(prev)
{
}

template<typename ItemType>
ItemType& LinkedList<ItemType>::ListNode::getDataRef() 
{ 
    return data_; 
}

template<typename ItemType>
ItemType LinkedList<ItemType>::ListNode::getData() const 
{ 
    return data_; 
}

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setData(const ItemType& data) 
{ 
    data_ = data; 
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNext() const 
{ 
    return next_; 
}

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToNext(ListNode* const next) 
{ 
    next_ = next; 
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrev() const 
{ 
    return prev_; 
}

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToPrev(ListNode* const prev) 
{ 
    prev_ = prev; 
}

template<typename ItemType>
std::ostream& operator<<(std::ostream& outputStream, const LinkedList<ItemType>& list)
{
    outputStream << "[";
    typename LinkedList<ItemType>::ListNode* current = list.getHead();
    while (current != nullptr)
    {
        outputStream << current->getData();
        if (current->getLinkToNext() != nullptr)
        {
            outputStream << ", ";
        }
        current = current->getLinkToNext();
    }
    outputStream << "]";
    return outputStream;
}

template<typename ItemType>
std::istream& operator>>(std::istream& inputStream, LinkedList<ItemType>& list)
{
    uint32_t count = 0;
    if (inputStream >> count)
    {
        LinkedList<ItemType> temp;
        for (uint32_t i = 0; i < count; ++i)
        {
            ItemType val;
            if (inputStream >> val)
            {
                temp.addToTail(val);
            }
        }
        list.swap(temp);
    }
    return inputStream;
}
