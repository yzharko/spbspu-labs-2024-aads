#include <fstream>
#include "execCommands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: Can't open a file!\n";
    return 2;
  }

  using base_t = proselkov::avlTree< int, std::string >;
  proselkov::avlTree< std::string, base_t > dataSets;

  proselkov::fillTree(input, dataSets);

  proselkov::avlTree< std::string, std::function< void(proselkov::avlTree< std::string, base_t >&) > > taskCmds;
  taskCmds.insert({ "print", proselkov::print });
  taskCmds.insert({ "complement", proselkov::complement });
  taskCmds.insert({ "intersect", proselkov::intersect });
  taskCmds.insert({ "union", proselkov::unio });

  while (!std::cin.eof())
  {
    std::string cmd;
    std::cin >> cmd;

    auto curCmd = taskCmds.find(cmd);
    if (curCmd == taskCmds.end() && cmd.length() > 0)
    {
      proselkov::outInvCommand(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    else if (cmd.length() > 0)
    {
      (*curCmd).second(dataSets);
    }
  }

  return 0;
}
