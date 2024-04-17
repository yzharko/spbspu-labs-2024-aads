#include <iostream>
#include <cstddef>
#include "ListProcess.hpp"

int main()
{
  using namespace reznikova;
  List< std::pair< std::string, List< size_t > > > list;
  List< size_t > sums;
  try
  {
    inputList(std::cin, list);
    sums = countSums(list);
    outputNames(std::cout, list);
    outputArgs(std::cout, list);
    outputSums(std::cout, sums);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
