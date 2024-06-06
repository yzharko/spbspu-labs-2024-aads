#ifndef SORTFUNCTIONS_HPP
#define SORTFUNCTIONS_HPP

namespace taskaev
{
  template <typename Iterator, typename Comparator >
  void Shaker(Iterator begin, Iterator end, Comparator comp);

  template <typename Iterator, typename Comparator >
  void Selection(Iterator begin, Iterator end, Comparator comp);
}

#endif
