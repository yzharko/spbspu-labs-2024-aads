#ifndef DATA_HPP
#define DATA_HPP

#include <iosfwd>
#include "list.hpp"

namespace batunov
{
  using listOfPairs = List< std::pair< std::string, List< size_t > > >;
  listOfPairs inputPair(std::istream& input);
  size_t findSize(listOfPairs& newList);
  void printListNames(listOfPairs& newList);
  void printValues(listOfPairs& newList, bool& overflowFlag, List< size_t >& sums);
  void getSums(List< size_t >& sums);
}

#endif
