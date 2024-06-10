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
  std::string names = argv[2];
  if (names != "ints" && names != "floats")
  {
    std::cerr << "Error:   typess errror\n";
    return 1;
  }
  size_t size = 0;
  try
  {
    size = std::stoll(argv[3]);
  }
  catch
  {
    std::cer << "eror\n";
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Error: size zero!\n";
    return 1;
  }
  //std::map < std::pair < std::string, std::string >, std::function< void(std::ostream&, size_t) > > cmds;
  //cmds[std::make_pair("ascending", "ints")] = taskaev::workSortings< int, std::less< int > >;
  //cmds[std::make_pair("ascending", "floats")] = taskaev::workSortings< float, std::less< float > >;
  //cmds[std::make_pair("descending", "ints")] = taskaev::workSortings< int, std::greater< int > >;
 // cmds[std::make_pair("descending", "floats")] = taskaev::workSortings< float, std::greater< float > >;
 // try
 // {
   // cmds.at(std::make_pair(std::string(argv[1]), std::string(argv[2])))(std::cout, size);
 // }
 // catch (const std::exception& e)
 // {
   // std::cerr << e.what();
   // return 1;
 // }
 // return 0;
}
