#ifndef WORKERBST_HPP
#define WORKERBST_HPP
#include <vector>
#include "BinarySearchTree.hpp"

class WorkerBST
{
  BinarySearchTree< std::string, BinarySearchTree< int, std::string >* > bst;

public:
  WorkerBST(const std::string& path);
  ~WorkerBST();
  void Menu();
private:
  void readFile(const std::string& path);
  void print(const std::string&);
  void complement(std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end);
  void intersect(std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end);
  void unify(std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end);
  void parseArguments(const std::string& str);
  int parseNum(const std::string& num);
  void readDataSet(const std::string& dataSet);
  void warningEmpty(std::ostream& out);
  void warningInvCom(std::ostream& out);
};
#endif
