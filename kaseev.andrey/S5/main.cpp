#include <iostream>
#include <functional>
#include <fstream>
#include "../common/BinarySearchTree.hpp"
#include "Traversal.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Wrong\n";
    return 1;
  }

  kaseev::BST< long long, std::string, std::less<long long> > dictionaries;
  kaseev::BST< std::string, std::function< void(kaseev::BST< long long, std::string, std::less<long long> > &) >, std::less<std::string>
      > cmds;

  cmds.insert(std::make_pair("ascending", kaseev::traverseAscending));
  cmds.insert(std::make_pair("descending", kaseev::traverseDescending));
  cmds.insert(std::make_pair("breadth", kaseev::traverseBreadth));

  try {
    std::ifstream file(argv[2]);
    if (!file) {
      throw std::runtime_error("Unable to open file");
    }

    long long key;
    std::string value;
    while (file >> key >> value) {
      dictionaries.push(key, value);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error loading file: " << e.what() << "\n";
    return 1;
  }

  try {
    std::string command = argv[1];
    auto commandIter = cmds.find(command);
    if (commandIter != cmds.end() && !command.empty()) {
      commandIter->second(dictionaries);
    }
    else if (!command.empty()) {
      kaseev::invalidCommandError(std::cerr);
      return 1;
    }
  } catch (const std::overflow_error &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
