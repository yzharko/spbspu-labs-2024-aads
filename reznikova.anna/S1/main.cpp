#include <iostream>
#include "List.hpp"
#include "ListIterator.hpp"
#include "Node.hpp"
#include "ListProcess.hpp"

int main()
{
  using namespace reznikova;
  bool overflow = 0;
  List< std::pair< std::string, List< int > > > list;
  try
  {
    inputList(std::cin, list, overflow);

    namesOutput(std::cout, list);
    std::cout << "\n";

    outputArgs(std::cout, list, overflow);
    std::cout << "\n";
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << "\n";
    return 0;
  }

  return 0;
}
