#ifndef LIST_PROCESS_HPP
#define LIST_PROCESS_HPP
#include "List.hpp"

namespace reznikova

{
  void inputList(std::istream & input, List< std::pair< std::string, List< size_t > > > & list, bool & overflow);
  void namesOutput(std::ostream & output, List< std::pair < std::string, List< size_t > > > & list);
  size_t findMaxLenOfArgs(List< std::pair < std::string, List< size_t > > > & list);
  void outputArgs(std::ostream & output, List< std::pair< std::string, List< size_t > > > & list, bool & overflow);
}

#endif
