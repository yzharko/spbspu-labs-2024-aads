#ifndef LIST_IO_HPP
#define LIST_IO_HPP
#include <istream>
#include <utility>
#include "list.hpp"

namespace smolyakov
{
  List<std::pair<std::string, List<long long>>> InputList(std::istream& inputStream);
}

#endif
