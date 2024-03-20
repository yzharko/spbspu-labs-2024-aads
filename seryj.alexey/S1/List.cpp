#include "List.hpp"
template<class T>
T& List<T>::operator[](size_t index)
{
  Iterator<T> curr_iter = begin;
  for (int i = 0; i < index; i++)
  {
    curr_iter++;
  }
  return *curr_iter;
}

template<class T>
bool List<T>::empty() const
{
  return begin == end;
}

template<class T>
void List<T>::push(T&& value)
{
}

template<class T>
void List<T>::pop()
{
  delete end.node;
  end--;
  
}
