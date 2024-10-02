#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "listIo.hpp"

int main()
{
  smolyakov::List<std::pair<std::string, smolyakov::List<long long>>> inputData = smolyakov::inputList(std::cin);
  smolyakov::List<long long> sums;
  smolyakov::List<smolyakov::List<long long>> rearrangedLists;

  if (inputData.isEmpty())
  {
    std::cout << 0 << '\n';
  }
  else
  {
    smolyakov::rearrangeValues(inputData, rearrangedLists);
    try
    {
      smolyakov::calculateSums(rearrangedLists, sums);
    }
    catch (std::overflow_error& e)
    {
      std::cout << e.what();
      return 1;
    }

    smolyakov::outputPairListNames(std::cout, inputData);
    smolyakov::outputRearrangedLists(std::cout, rearrangedLists);
    smolyakov::outputListValues(std::cout, sums);
  }
  return 0;
}
