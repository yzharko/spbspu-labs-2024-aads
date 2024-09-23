#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "commands.hpp"
#include "tree.hpp"

int main(int argc, char** argv)
{
  using namespace gorbunova;
  if (argc != 3)
  {
    std::cerr << "Error: arguments invalid!\n";
    return 1;
  }
  Tree<int, std::string> tree;
  std::fstream inputs(argv[2]);
  if (!inputs)
  {
    std::cerr << "Error: not open file!\n";
    return 1;
  }
  std::string name = argv[1];
  try
  {
    buildTree(inputs, tree);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  Tree<std::string, std::function<void(Tree<int, std::string>&)>> cmds;
  cmds.insert("ascending", ascending);
  cmds.insert("descending", descending);
  cmds.insert("breadth", breadth);
  try
  {
    cmds.at(name)(tree);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
