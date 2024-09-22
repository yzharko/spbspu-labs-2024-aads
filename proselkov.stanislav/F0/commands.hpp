#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <AVLTree.hpp>

namespace proselkov
{
  using langDictionary = name::avlTree< std::string, std::string >;
  using majorDictionary = name::avlTree< std::string, langDictionary >;

  void helpCmd(std::istream& in, std::ostream& out);
  void createCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void removeCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void printCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void clearCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void deleteCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void insertCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void searchCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void sizeCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void editCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void combineCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void saveCmd(majorDictionary& major, std::istream& in, std::ostream& out);
}

#endif
