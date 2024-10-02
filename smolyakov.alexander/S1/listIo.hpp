#ifndef LIST_IO_HPP
#define LIST_IO_HPP
#include <istream>
#include <utility>
#include "list.hpp"

namespace smolyakov
{
  using listOfPairs = smolyakov::List<std::pair<std::string, smolyakov::List<size_t>>>;
  listOfPairs inputList(std::istream& inputStream);
  void outputPairListNames(std::ostream& outputStream, listOfPairs list);
  void rearrangeValues(listOfPairs& listOfPairs, List<smolyakov::List<size_t>>& lists);
  void outputRearrangedLists(std::ostream& outputStream, List<List<size_t>>& lists);
  void calculateSums(List<List<size_t>>& lists, List<size_t>& destination);
  void outputListValues(std::ostream& outputStream, List<size_t>& list);
}

#endif
