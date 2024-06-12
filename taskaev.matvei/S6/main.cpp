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
  std::string names = argv[1];
  if (names != "ascending" && names != "descending")
  {
    std::cerr << "Error:   AAA\n";
    return 1;
  }
  std::string types = argv[2];
  if (types != "ints" && types != "floats")
  {
    std::cerr << "Error:   typess errror\n";
    return 1;
  }
  size_t size = 0;
  try
  {
    size = std::stoll(argv[3]);
  }
  catch(...)
  {
    std::cerr << "eror\n";
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Error: size zero!\n";
    return 1;
  }
  std::map< std::string, std::map< std::string, std::function< void(std::ostream&, std::string, size_t) > > > cmds{};
  using namespace std::placeholders;
  cmds["ascending"]["ints"] = std::bind(workSortings< int, std::less< int > >, _1, _2 _3, std::less< int >{});
  cmds["ascending"]["floats"] = std::bind(workSortings< float, std::less< float > >, _1, _2 _3, std::less< float >{});
  cmds["descending"]["ints"] = std::bind(workSortings< int, std::less< int > >, _1, _2 _3, std::less< int >{});
  cmds["desscending"]["floats"] = std::bind(workSortings< float, std::greater< float > >, _1, _2 _3, std::greater< float >{});
  try
  {
    cmds.at(names).at(types)(std::cout, type, size);
  }
  catch(const std::exception&)
  {
    std::cerr << "ERROR: SOSSS!\n";
    return 1;
  }
  return 0;
}
