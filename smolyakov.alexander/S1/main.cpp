#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "listIo.hpp"

int main()
{
  smolyakov::List<std::pair<std::string, smolyakov::List<size_t>>> inputData = smolyakov::inputList(std::cin);
  smolyakov::List<size_t> sums;
  smolyakov::List<smolyakov::List<size_t>> rearrangedLists;

  if (inputData.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  smolyakov::outputPairListNames(std::cout, inputData);
  
  smolyakov::rearrangeValues(inputData, rearrangedLists);
  if (rearrangedLists.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  try
  {
    smolyakov::calculateSums(rearrangedLists, sums);
  }
  catch (std::overflow_error& e)
  {
    std::cout << e.what();
    return 1;
  }

  smolyakov::outputRearrangedLists(std::cout, rearrangedLists);
  smolyakov::outputListValues(std::cout, sums);
  return 0;
}
