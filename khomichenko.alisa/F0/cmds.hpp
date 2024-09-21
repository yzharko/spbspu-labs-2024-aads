#ifndef CMDS_HPP
#define CMDS_HPP
#include <iostream>
#include <string>
#include "list.hpp"
#include "binarySearchTree.hpp"
namespace khomichenko
{
  void addDictionary(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void deleteDictionary(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void addWord(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void removeWord(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void translate(std::ostream&, std::istream&, const Tree< std::string, Tree< std::string, List< std::string > > >&);
  void mergeDictionaries(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void getIntersection(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void getCombining(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
  void getDifference(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&);
}

#endif
