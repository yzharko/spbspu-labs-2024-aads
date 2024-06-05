#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <fstream>
#include "Tree.hpp"

namespace reznikova
{
  void outputInvalidCommand(std::ostream & out);
  void outputError(std::ostream & out);
  std::string getValue(std::string & input, size_t & i);
  size_t getKey(std::string & input, size_t & i);
  void readFromFile(std::ifstream & is, Tree< std::string, Tree< size_t, std::string > > & treeMap);
  void print(Tree< std::string, Tree< size_t, std::string > > & treeMap);
  void complement(Tree< std::string, Tree< size_t, std::string > > & treeMap);
}
#endif
