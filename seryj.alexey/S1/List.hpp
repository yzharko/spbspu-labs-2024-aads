#ifndef LIST_HPP
#define LIST_HPP
template <class T>
struct List
{
  T data;
  List<T>* next;
};
#endif
