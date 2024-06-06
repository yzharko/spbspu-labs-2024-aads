// #include <map>
#include <functional>
#include <string>
#include <AVLtree.hpp>
#include "IOprocessing.hpp"
#include "details.hpp"

int main(int argc, char *argv[])
{
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
  if (size == 0)
  {
    mihalchenko::printWrongSize(std::cout);
    return 1;
  }
  mihalchenko::AVLTree<std::string, mihalchenko::AVLTree<std::string, std::function<void(std::ostream &, size_t)>>> cmds;
  {
    using namespace std::placeholders;
    cmds["floats"]["ascending"] = std::bind(mihalchenko::testSorts<double, std::less<double>>, _1, _2, std::less<double>{});
    cmds["floats"]["descending"] = std::bind(mihalchenko::testSorts<double, std::greater<double>>, _1, _2, std::greater<double>{});
    cmds["ints"]["ascending"] = std::bind(mihalchenko::testSorts<int, std::less<int>>, _1, _2, std::less<int>{});
    cmds["ints"]["descending"] = std::bind(mihalchenko::testSorts<int, std::greater<int>>, _1, _2, std::greater<int>{});
  }
  if (cmds.find(argv[2]) == cmds.end())
  {
    mihalchenko::printWrongInput(std::cout);
    return 1;
  }
  try
  {
    cmds.at(argv[2]).at(argv[1])(std::cout, size);
  }
  catch (const std::out_of_range &)
  {
    mihalchenko::printWrongInput(std::cout);
    return 1;
  }
  return 0;
}
