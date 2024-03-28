#ifndef MAIN_UTILS_HPP
#define MAIN_UTILS_HPP

#include "list.hpp"

using SI_pair = std::pair< std::string, miheev::List< size_t > >;
using ListIter = miheev::List<size_t>::Iterator;

namespace miheev
{
  template <class T>
  void pPrint(T* arr, size_t size);
  void expandPairsArr(SI_pair*& pairs, size_t& size);
  List< size_t > readNumbers(std::istream& stream);
  SI_pair getSIPair(std::istream& stream);
  ListIter* getIters(SI_pair* pairs, size_t size);
  List< size_t >* getLists(SI_pair* pairs, size_t size);
  size_t maxListSize(List< size_t >* lists, size_t size);
}

template <class T>
void miheev::pPrint(T* arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    std::cout << arr[i];
    if (i < size - 1)
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}

#endif
