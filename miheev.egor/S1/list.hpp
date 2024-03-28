#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iostream>
#include <memory>

namespace miheev
{
  template< typename T >
  class List
  {
  public:
    T data_;
    List< T >* next_;
    bool isEmpty_;
    struct Iterator;

    List():
      data_(0),
      next_(nullptr),
      isEmpty_(true)
    {}

    List(T data):
      data_(data),
      next_(nullptr),
      isEmpty_(false)
    {}

    List(const List& toCopy)
    {
      data_ = toCopy.data_;
      isEmpty_ = toCopy.isEmpty_;
      if (toCopy.next_)
      {
        next_ = new List< T >(*toCopy.next_);
      }
      else
      {
        next_ = nullptr;
      }
    }

    List(List&& rhs) noexcept
    {
      data_ = rhs.data_;
    }

    explicit List(size_t count, T value):
      next_(nullptr),
      isEmpty_(true)
    {
      for (size_t i = 0; i < count; i++)
      {
        pushBack(value);
      }
    }

    List& operator= (const List& list)
    {
      data_ = list.data_;
      isEmpty_ = list.isEmpty_;
      if (next_)
      {
        List< T >* old = next_;
        next_ = nullptr;
        delete old;
      }
      if (list.next_)
      {
        next_ = new List< T >(*(list.next_));
      }
      return *this;
    }

    ~List()
    {
      if (next_)
      {
        delete next_;
      }
    }

    bool empty()
    {
      return isEmpty_;
    }

    void swap(List< T >& aList)
    {
      List< T > temp = *this;
      clear();
      while (!aList.empty())
      {
        pushBack(aList.front());
        aList.popFront();
      }
      aList.clear();
      while (!temp.empty())
      {
        aList.pushBack(temp.front());
        temp.popFront();
      }
    }

    void clear()
    {
      if (next_ != nullptr)
      {
        List< T >* temp = next_;
        next_ = nullptr;
        delete temp;
      }
      isEmpty_ = true;
      data_ = 0;
    }

    size_t size() const
    {
      if (isEmpty_)
      {
        return 0;
      }
      if (!next_)
      {
        return 1;
      }
      return 1 + next_->size();
    }

    T& front()
    {
      return data_;
    }

    void pushFront(T data)
    {
      if (!isEmpty_)
      {
        List< T >* temp = next_;
        next_ = new List< T >(data_);
        next_->next_ = temp;
      }
      data_ = data;
      isEmpty_ = false;
    }

    void popFront()
    {
      if (!next_)
      {
        data_ = 0;
        isEmpty_ = true;
      }
      if (isEmpty_)
      {
        return;
      }
      List< T >* temp = next_;
      data_ = next_->data_;
      next_ = next_->next_;
      temp->next_ = nullptr;
      delete temp;
    }

    void pushBack(T data)
    {
      if (isEmpty_)
      {
        data_ = data;
      }
      else
      {
        if (next_ == nullptr)
        {
          next_ = new List< T >(data);
        }
        else
        {
          next_->pushBack(data);
        }
      }
      isEmpty_ = false;
    }

    void print(std::ostream& stream = std::cout, const char& splitter = ' ') const
    {
      stream << data_ << splitter;
      if (next_)
      {
        next_->print(stream, splitter);
      }
      else
      {
        std::cout << '\n';
      }
    }

    Iterator begin()
    {
      return this;
    }
    Iterator end()
    {
      return nullptr;
    }

    struct ConstIterator
    {

    };

    struct Iterator
    {
      List<T>* cur;
      using this_t = List< T >::Iterator;
      Iterator():
        cur(nullptr)
      {}
      Iterator(List< T >* head):
        cur(head)
      {}
      Iterator(const this_t&) = default;
      this_t& operator=(const this_t&) = default;
      List<T>& operator+(size_t n)
      {
        for (; n > 0; n--)
        {
          cur++;
        }
        return cur;
      }

      T& operator*()
      {
        return cur->data_;
      }

      T* operator->() const
      {
        return std::addressof(cur->data_);
      }

      explicit operator bool() const
      {
        return cur->next_ != nullptr;
      }

      bool empty() const
      {
        return cur->isEmpty_;
      }

      this_t& operator++()
      {
        cur = cur->next_;
        return *this;
      }

      this_t operator++(int)
      {
        this_t copy(*this);
        cur = cur->next_;
        return *copy;
      }

      bool operator!=(const this_t & rhs) const
      {
        return cur != rhs.cur;
      }

      bool operator==(const this_t & rhs) const
      {
        return cur == rhs.cur;
      }
    };
  };
}

#endif
