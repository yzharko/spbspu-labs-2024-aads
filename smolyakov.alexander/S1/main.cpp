#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "listIo.hpp"

int main()
{
  smolyakov::List<size_t> sums;
  smolyakov::List<smolyakov::List<size_t>> rearrangedLists;

  try
  {
    smolyakov::List<std::pair<std::string, smolyakov::List<size_t>>> inputData = smolyakov::inputList(std::cin);

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

    smolyakov::calculateSums(rearrangedLists, sums);

    smolyakov::outputRearrangedLists(std::cout, rearrangedLists);
    smolyakov::outputListValues(std::cout, sums);
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
