#include <iostream>
#include <cstddef>
#include "ListProcess.hpp"

int main()
{
  using namespace reznikova;
  bool overflow = 0;
  List< std::pair< std::string, List< size_t > > > list;
  try
  {
    inputList(std::cin, list, overflow);
    namesOutput(std::cout, list);
    outputArgs(std::cout, list, overflow);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
