#include <map>
#include <functional>
#include <string>
#include <cstdlib>
#include <time.h>
#include <AVLtree.hpp>
#include "IOprocessing.hpp"
#include "details.hpp"

int main(int argc, char *argv[])
{
  srand(time(0));
  if (argc != 4)
  {
    mihalchenko::printWrongInput(std::cout);
    return 1;
  }
  size_t size = 0;
  if (isdigit(argv[3][0]))
  {
    size = std::stoull(argv[3]);
  }
  else
  {
    mihalchenko::printWrongSize(std::cout);
    return 1;
  }
  if (size < 1)
  {
    mihalchenko::printWrongSize(std::cout);
    return 1;
  }
  std::map<std::string, mihalchenko::AVLTree<std::string, std::function<void(std::ostream &, size_t)>>> cmds;
  using namespace std::placeholders;
  cmds["floats"]["ascending"] = std::bind(mihalchenko::testSorts<int, std::less<int>>, _1, _2, std::less<int>{});
  cmds["floats"]["descending"] = std::bind(mihalchenko::testSorts<int, std::greater<int>>, _1, _2, std::greater<int>{});
  cmds["ints"]["ascending"] = std::bind(mihalchenko::testSorts<double, std::less<double>>, _1, _2, std::less<double>{});
  cmds["ints"]["descending"] = std::bind(mihalchenko::testSorts<double, std::greater<double>>, _1, _2, std::greater<double>{});
  try
  {
    cmds.at(argv[1]).at(argv[2])(std::cout, size);
  }
  catch (const std::exception &)
  {
    mihalchenko::printWrongInput(std::cout);
    return 1;
  }
  return 0;
}
