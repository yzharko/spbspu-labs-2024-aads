#ifndef LIST_ITEM_HPP
#define LIST_ITEM_HPP
namespace zheleznyakov
{
  template <typename T>
  class ListItem
  {
  public:
    ListItem(T value, ListItem<T> *next = nullptr, ListItem<T> *prev = nullptr);
    T value;
    ListItem<T> *next;
    ListItem<T> *prev;
  };
}

template <typename T>
zheleznyakov::ListItem<T>::ListItem(T value, ListItem<T> *next, ListItem<T> *prev) : value(value), next(next), prev(prev)
{
}
#endif
