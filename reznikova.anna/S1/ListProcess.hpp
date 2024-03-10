#ifndef LIST_PROCESS_HPP
#define LIST_PROCESS_HPP
#include "List.hpp"
#include "Node.hpp"
#include "ListIterator.hpp"

namespace reznikova

{
  void inputList(std::istream & input, List< std::pair< std::string, List<int> > > & list);
  void namesOutput(std::ostream & output, List< std::pair < std::string, List< int > > > & list);
  size_t findMaxLenOfArgs(List< std::pair < std::string, List< int > > > & list);
  void outputArgs(std::ostream & output, List< std::pair< std::string, List< int > > > & list);
}

#endif
