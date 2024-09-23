#ifndef ITER_PRINT_HPP
#define ITER_PRINT_HPP

#include <iostream>

namespace sadofeva
{
  template <typename Iter>
  void print(Iter first, Iter last, std::ostream & out);
}

template <typename Iter>
void sadofeva::print(Iter first, Iter last, std::ostream & out)
{
  bool first_val = true;
  while (first != last)
  {
    if (first_val)
    {
      first_val = false;
    }
    else
    {
      out << ' ';
    }
    out << *first;
    ++first;
  }
  out << '\n';
}

#endif

