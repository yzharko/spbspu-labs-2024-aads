#ifndef WORKERBST_HPP
#define WORKERBST_HPP
#include "BinarySearchTree.hpp"
#include <vector>

class WorkerBST
{
  BinarySearchTree<std::string, BinarySearchTree<int, std::string>* > bst;
public:
  WorkerBST(const std::string& path);
  ~WorkerBST();
  void Menu();
private:
  void ReadFile(const std::string& path);
  void Print(const std::string&);
  void Complement(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
  void Intersect(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
  void Union(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
  void ParseArguments(const std::string& str);
  int ParseNum(const std::string& num);
  void ReadDataSet(const std::string& dataSet);
};

#endif
