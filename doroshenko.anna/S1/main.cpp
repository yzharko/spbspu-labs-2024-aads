#include <limits>
#include "list.hpp"
#include "functions.hpp"

int main()
{
  using namespace doroshenko;
  try
  {
    List< std::pair< std::string, List< size_t > > > list = listInput(std::cin);
    listOutput(list, std::cout);
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
