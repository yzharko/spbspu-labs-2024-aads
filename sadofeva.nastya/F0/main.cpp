#include <iostream>
#include <functional>
#include <vector>
#include <sstream>
#include "AVLTree.hpp"
#include "command.hpp"
#include "dict.hpp"

int main() {
  using cmdType = std::function< void(std::istream&, std::ostream&, std::vector< sadofeva::Dict >&) >;
  std::vector< sadofeva::Dict > dicts;
  sadofeva::AVLTree< std::string, cmdType > commandsMap;
  commandsMap.insert("save", sadofeva::save);
  commandsMap.insert("print", sadofeva::print);
  commandsMap.insert("printMaxCountWords", sadofeva::printMaxCountWords);
  commandsMap.insert("search", sadofeva::search);
  commandsMap.insert("clear", sadofeva::clear);
  commandsMap.insert("load", sadofeva::load);
  commandsMap.insert("remove", sadofeva::remove);
  commandsMap.insert("count", sadofeva::count);
  commandsMap.insert("union", sadofeva::unionData);
  commandsMap.insert("insert", sadofeva::insert);
  commandsMap.insert("intersect", sadofeva::intersect);
  commandsMap.insert("size", sadofeva::getSize);
  std::string command;
  while (std::cin >> command) {
    if (commandsMap.find(command) != commandsMap.end()) {
      commandsMap.at(command)(std::cin, std::cout, dicts);
    } else {
      std::cout << "Invalid command: " << command << '\n';
    }
  }
  return 0;
}
