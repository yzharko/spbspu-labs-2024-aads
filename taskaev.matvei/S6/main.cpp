
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <utility>
#include "sortFunctions.hpp"
#include "workSort.hpp"

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
  std::map < std::pair < std::string, std::string >, std::function< void(size_t, std::ostream&) > > cmds;
  cmds[std::make_pair("ascending", "ints")] = workSortings< int, std::less< int > >;
  cmds[std::make_pair("ascending", "floats")] = workSortings< float, std::less< float > >;
  cmds[std::make_pair("descending", "ints")] = workSortings< int, std::greater< int > >;
  cmds[std::make_pair("descending", "floats")] = workSortings< float, std::greater< float > >;

  try
  {
    cmds.at(std::make_pair(std::string(argv[1]),std::string(argv[2])))(size, std::cout);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
