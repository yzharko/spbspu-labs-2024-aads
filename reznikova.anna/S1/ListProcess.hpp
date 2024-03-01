#ifndef ListProcess_hpp
#define ListProcess_hpp

#include "List.hpp"
#include "Node.hpp"
#include "ListIterator.hpp"
#include <utility>

namespace reznikova

{
  void inputList(std::istream & input, List< std::pair< std::string, List<int> > > & list);
  void namesOutput(std::ostream & output, List< std::pair < std::string, List< int > > > & list);
  size_t findMaxLenOfArgs(List< std::pair < std::string, List< int > > > & list);
}

#endif
