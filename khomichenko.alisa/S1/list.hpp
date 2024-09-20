#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
template< typename T >
class List {
public:
    List() :
        size(0),
        head(nullptr),
        ending(nullptr)
    {};
    List(const List& other) = default;
    ~List() = default;

    void pushBack(T data);
    void pushFront(T data);
    bool empty();
    void print();
    void popFront();
    void clear();
    void swap(List* other);

    class Iterator;
    class ConstIterator;
    Iterator begin();
    Iterator end();
private:
    class Node {
    public:
        friend class List;
        Node(T value) :
            data(value),
            next(nullptr)
        {}
    private:
        T data;
        Node* next;
    };
    size_t size;
    Node * head;
    Node * ending;
};

template <typename T>
bool List<T>::empty()
{
    return (head == nullptr);
}

template <typename T>
void List<T>::pushBack(T data)
{
    Node* pushed = new Node(data);
    if (head != nullptr)
    {
        ending->next = pushed;
    }
    else
    {
        head = pushed;
    }
    ending = pushed;
    size += 1;
    delete pushed;
}

template <typename T>
void List<T>::pushFront(T data)
{
    Node* pushed = new Node(data);
    if (size > 0)
    {
        pushed->next = head;
        head = pushed;
    }
    head = pushed;
    size += 1;
    delete pushed;
}

template <typename T>
void List<T>::print()
{
    Node* go = head;
    while (go != nullptr)
    {
        std::cout << go->data << " ";
        go = go->next;
    }
    std::cout << "\n";
}

template <typename T>
void List<T>::popFront()
{
    if (head == ending)
    {
        delete head;
        head = nullptr;
        ending = nullptr;
    }
    else
    {
        Node* todel = head;
        head = head->next;
        delete todel;
    }
}

template <typename T>
void List<T>::clear()
{
    while (head != nullptr)
    {
        popFront();
    }
}

template <typename T>
void List<T>::swap(List* other)
{
    if (size == other->size)
    {
        std::swap(head, other->head);
        std::swap(ending, other->ending);
    }
    else
    {
        std::cerr << "error: different size\n";
    }

}


template <typename T>
class List<T>::Iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    friend class List<T>;
    Iterator();
    Iterator(List<T>::Node * ptr);
    ~Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator= (const Iterator&) = default;
    Iterator& operator++();
    Iterator operator++(int);
    T& operator*();
    T* operator->();
    bool operator!=(Iterator rhs);
    bool operator==(Iterator rhs);
    Node * node;
};

template <typename T>
List<T>::Iterator::Iterator() :
    node (nullptr)
{}

template <typename T>
List<T>::Iterator::Iterator(Node * ptr) :
    node (ptr)
{}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    node = node->next;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator result(*this);
    ++(*this);
    return result;
}

template <typename T>
T& List<T>::Iterator::operator*()
{
    return node->data;
}

template <typename T>
T* List<T>::Iterator::operator->()
{
    return std::addressof(node->data);
}

template <typename T>
bool List<T>::Iterator::operator==(List<T>::Iterator rhs)
{
    return node == rhs.node;
}

template <typename T>
bool List<T>::Iterator::operator!=(List<T>::Iterator rhs)
{
    return !(rhs == *this);
}

template <typename T>
typename List<T>::Iterator List<T>::begin()
{
    return Iterator(head);
};

template <typename T>
typename List<T>::Iterator List<T>::end()
{
    return Iterator(ending);
};

#endif
