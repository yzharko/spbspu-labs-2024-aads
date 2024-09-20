#include <fstream>
#include <sstream>
#include "ABLtree.hpp"
#include "Command.hpp"

using namespace sadofeva;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File not provided" << "\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Error:Unable to open file" << "\n";
    return 1;
  }
  std::map<std::string, BinarySearchTree<int, std::string>> dicts;
  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string datasetName;
    iss >> datasetName;
    BinarySearchTree<int, std::string> tree;
    int key;
    std::string value;
    while (iss >> key >> value)
    {
       tree.push(key, value);
    }
    dicts[datasetName] = std::move(tree);
  }
  file.close();
  std::string commandLine;
  while (std::getline(std::cin, commandLine))
  {
    std::istringstream iss(commandLine);
    std::string command;
    iss >> command;
    if (command == "print")
    {
      std::string dataset;
      iss >> dataset;
      handlePrint(dicts, dataset);
    }
    else if (command == "complement")
    {
      std::string newDataset, dataset1, dataset2;
      iss >> newDataset >> dataset1 >> dataset2;
      handleComplement(dicts, newDataset, dataset1, dataset2);
    }
    else if (command == "intersect")
    {
      std::string newDataset, dataset1, dataset2;
      iss >> newDataset >> dataset1 >> dataset2;
      handleIntersect(dicts, newDataset, dataset1, dataset2);
    }
    else if (command == "union")
    {
      std::string newDataset, dataset1, dataset2;
      iss >> newDataset >> dataset1 >> dataset2;
      handleUnion(dicts, newDataset, dataset1, dataset2);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
  }
  return 0;
}
