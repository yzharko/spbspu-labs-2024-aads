
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <utility>
#include "sortFunctions.h"
#include "workSort.h"

int main(int argc, char **argv)
{
  using namespace taskaev;
  if (argc != 4)
  {
    std::cerr << "Error:\n";
    return 1;
  }

  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Error: size zero!\n";
    return 1;
  }
  std::map < std::pair < std::string, std::string >, std::function< void(std::ostream&, size_t) > > cmds;
  cmds[std::make_pair("ints", "ascending")] = workSortings< int, std::less< int > >;
  cmds[std::make_pair("floats","ascending")] = workSortings< float, std::less< float > >;
  cmds[std::make_pair("ints", "descending")] = workSortings< int, std::greater< int > >;
  cmds[std::make_pair("floats", "descending")] = workSortings< float, std::greater< float > >;

  try
  {
    cmds.at(std::make_pair(std::string(argv[1]),std::string(argv[2])))(std::cout, size);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
