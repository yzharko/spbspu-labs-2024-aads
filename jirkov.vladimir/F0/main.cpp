#include <functional>
#include <limits>
#include <iostream>
#include "commands.hpp"

int main()
{
  using dictionary = BST< std::string, std::string >;
  BST< std::string, dictionary > dicts;
  BST< std::string, std::function< void(BST< std::string, dictionary >&, std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands.insert("help", std::bind(jirkov::help, _3));
    commands.insert("create", std::bind(jirkov::createDict, _1, _2, _3));
    commands.insert("remove", std::bind(jirkov::removeDict, _1, _2, _3));
    commands.insert("print", std::bind(jirkov::printDict, _1, _2, _3));
    commands.insert("sort", std::bind(jirkov::sortDict, _1, _2, _3));
    commands.insert("write", std::bind(jirkov::writeToFile, _1, _2, _3));
    commands.insert("top", std::bind(jirkov::printTop, _1, _2, _3));
  }
  std::string cmd;
  while (std::cin >> cmd && cmd != "save")
  {
    try
    {
      commands.at(cmd).second(dicts, std::cin, std::cout);
    }
    catch (const std::out_of_range& e)
    {
      warningInvCom(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
