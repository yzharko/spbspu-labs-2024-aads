#ifndef LIST_IO_HPP
#define LIST_IO_HPP
#include <istream>
#include <utility>
#include "list.hpp"

namespace smolyakov
{
  using listOfPairs = smolyakov::List<std::pair<std::string, smolyakov::List<long long>>>;
  listOfPairs inputList(std::istream& inputStream);
  void outputPairListNames(std::ostream& outputStream, listOfPairs list);
  void rearrangeValues(listOfPairs& listOfPairs, List<smolyakov::List<long long>>& lists);
  void outputRearrangedLists(std::ostream& outputStream, List<List<long long>>& lists);
  void calculateSums(List<List<long long>>& lists, List<long long>& destination);
  void outputListValues(std::ostream& outputStream, List<long long>& list);
}

#endif
