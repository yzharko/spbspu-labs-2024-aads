#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <limits>
#include "tree.hpp"
#include "commands.hpp"

using namespace gorbunova;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: argument of file failed!\n";
    return 1;
  }

  MainTree mainTree;
  std::ifstream inputFile(argv[1]);

  if (!inputFile)
  {
    std::cerr << "Error: input\n";
    return 1;
  }

  buildTree(inputFile, mainTree);

  Tree<std::string, std::function<void(MainTree&)>> commandMap;
  commandMap.insert("print", displayTree);
  commandMap.insert("complement", computeComplement);
  commandMap.insert("intersect", computeIntersection);
  commandMap.insert("union", computeUnion);

  std::string command;

  while (std::cin >> command)
  {
    try
    {
      commandMap.at(command)(mainTree);
    }
    catch (const std::out_of_range& e)
    {
      displayInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}
