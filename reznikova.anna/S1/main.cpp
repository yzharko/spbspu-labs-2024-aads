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

    outputArgs(std::cout, list);
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
