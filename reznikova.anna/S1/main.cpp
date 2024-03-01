#include <iostream>
#include "List.hpp"
#include "ListIterator.hpp"
#include "Node.hpp"
#include "ListProcess.hpp"

int main()
{
  using namespace reznikova;
  List< std::pair< std::string, List< int > > > list;
  try
  {
    inputList(std::cin, list);
    namesOutput(std::cout, list);
    std::cout << "\n";
  }
  catch (...)
  {
    //?
  }
  return 0;
}
