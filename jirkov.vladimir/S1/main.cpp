#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"
#include "calculatingData.hpp"

int main()
{
  using namespace jirkov;
  try
  {
    List< std::pair< std::string, List< size_t > > > newList = inputPair(std::cin);
    if (findSize(newList) == 0)
    {
      if (!newList.empty())
      {
        printListNames(newList);
      }
      std::cout << "0\n";
    }
    else
    {
      printListNames(newList);
      bool overflowFlag = false;
      List< size_t > sums;
      printValues(newList, overflowFlag, sums);
      if (!overflowFlag)
      {
        getSums(sums);
      }
    }
  }
  catch (std::overflow_error const & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
