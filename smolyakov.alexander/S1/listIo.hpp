#ifndef LIST_IO_HPP
#define LIST_IO_HPP
#include <istream>
#include <utility>
#include "list.hpp"

namespace smolyakov
{
  List<std::pair<std::string, List<long long>>> inputList(std::istream& inputStream);
  void outputPairListNames(std::ostream& outputStream, List<std::pair<std::string, smolyakov::List<long long>>> list);
}

#endif
