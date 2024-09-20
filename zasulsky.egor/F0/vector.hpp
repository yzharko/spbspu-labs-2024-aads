#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>
template <typename T>
class Vector;

template <typename T >
class Iterator : public std::iterator < std::bidirectional_iterator_tag, T >
{
public:
  friend Vector<T>;
private:
  T* ptr;

public:
  Iterator(T* ptr) : ptr(ptr) {}

  T& operator*() const
  {
    return *ptr;
  }

  Iterator& operator++()
  {
    ++ptr;
    return *this;
  }
  Iterator& operator--()
  {
    --ptr;
    return *this;
  }

  Iterator operator++(int)
  {
    Iterator temp = *this;
    ++ptr;
    return temp;
  }
  Iterator operator--(int)
  {
    Iterator temp = *this;
    --ptr;
    return temp;
  }

  bool operator==(const Iterator& other) const
  {
    return ptr == other.ptr;
  }

  bool operator!=(const Iterator& other) const
  {
    return ptr != other.ptr;
  }
};

template <typename T>
class Vector
{
  friend class Iterator<T>;
private:
  T* data;

  size_t size;
  size_t capacity;

public:
  Vector() :
    data(nullptr),
    size(0),
    capacity(0)
  {}

  Vector(const Vector& other) : size(other.size), capacity(other.capacity)
  {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i)
    {
      data[i] = other.data[i];
    }
  }

  ~Vector()
  {
    delete[] data;
  }

  Vector& operator=(const Vector& other)
  {
    if (this != &other)
    {
      delete[] data;
      size = other.size;
      capacity = other.capacity;
      data = new T[capacity];
      for (size_t i = 0; i < size; ++i)
      {
        data[i] = other.data[i];
      }
    }
    return *this;
  }

  T& operator[](size_t index)
  {
    return data[index];
  }

  Iterator<T> begin()
  {
    return Iterator<T>(data);
  }

  Iterator<T> end()
  {
    return Iterator<T>(data + size);
  }
  void push_back(const T& value)
  {
    if (size >= capacity)
    {
      size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
      T* new_data = new T[new_capacity];
      for (size_t i = 0; i < size; ++i)
      {
        new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
      capacity = new_capacity;
    }
    data[size++] = value;
  }

  size_t getSize() const
  {
    return size;
  }

  void erase(size_t index)
  {
    if (index >= size)
    {
      throw std::out_of_range("Index out of bounds");
    }
    for (size_t i = index; i < size - 1; ++i)
    {
      data[i] = data[i + 1];
    }
    --size;
  }

  void erase(const Iterator<T>& it)
  {
    if (it.ptr < data || it.ptr >= data + size)
    {
      // Обработка ошибки: переданный итератор не принадлежит вектору
      throw std::out_of_range("Iterator is out of bounds");
    }

    size_t index = it.ptr - data;
    for (size_t i = index; i < size - 1; ++i)
    {
      data[i] = data[i + 1];
    }
    --size;
  }

  void clear()
  {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
  }

  T& back()
  {
    if (size == 0)
    {
      throw std::out_of_range("Vector is empty");
    }
    return data[size - 1];
  }

  T& front()
  {
    if (size == 0)
    {
      throw std::out_of_range("Vector is empty");
    }
    return data[0];
  }

};

#endif
