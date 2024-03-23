#ifndef LIST_HPP
#define LIST_HPP

namespace ponomarev
{
  template< typename T >
  class List
  {
    class ConstIterator;

    List();
    ~List();

    //перегрузки операторов

    void clear();
    void push(const T &value);

    //итераторы

    private:
      struct ListNode
      {
        T data;
        ListNode *next;
        ListNode(const T &d, ListNode *n);
      };

      ListNode *head;
      ListNode *tail;
  };
}

template< typename T >
class List< T >::ConstIterator
{
  public:
    friend class List< T >;
    using this_t = ConstIterator;

    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);

    const T & operator*() const;
    const T * operator->() const;

    bool opetaror!=(const this_t &) const;
    bool operator==(const this_t &) const;
  private:
    ListNode * node_;
    ConstIterator(ListNode*, const List< T >*);
};


template< typename T >
ponomarev::List< T >::List():
  head(nullptr),
  tail(nullptr)
{}

template< typename T >
ponomarev::List< T >::~List()
{
  clear();
}

template< typename T >
void ponomarev::List< T >::clear()
{
  while (head)
  {
    head = head->next;
    delete head->prev;
  }
}

template< typename T >
void ponomarev::List< T >::push(const T & value)
{
  ListNode * data = new ListNode(value);
  if (head == tail == nullptr)
  {
    head->next = data;
    tail->prev = data;
  }
  else
  {
    ListNode * temp = tail->prev;
    temp->next = data;
    tail->prev = data;
  }
}
#endif
