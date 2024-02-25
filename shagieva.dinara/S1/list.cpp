template< typename T >
class List
{
private:
  struct Link
  {
    Link * prev;
    Link * next;
    T data;
  };

  Link * first;
  Link * last;

public:
  class iterator
  {
  private:
    Link * curr;

  public:
    iterator(Link * p) :
      curr(p)
    {}

    T operator*()
    {
      return curr->data;
    }

    iterator operator++()
    {
      curr = curr->next;
      return *this;
    }

    iterator operator++(int)
    {
      iterator it = *this;
      curr = curr->next;
      return it;
    }

    iterator operator--()
    {
      curr = curr->prev;
      return *this;
    }

    iterator operator--(int)
    {
      iterator it = *this;
      curr = curr->prev;
      return it;
    }

    bool operator==(const iterator & other) const
    {
      return curr == other.curr;
    }

    bool operator!=(const iterator & other) const
    {
      return curr != other.curr;
    }
  };

  iterator begin();
  iterator end();
  iterator insert(iterator p, const T& v);
  iterator erase(iterator p);
  void push_back(const T& v);
  void push_front(const T& v);
  void pop_front();
  void pop_back();

  T& front();
  T& back();
};
