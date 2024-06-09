#include <iostream>
#include <fstream>
#include "BinarySearchTree.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include "WorkerBST.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error!";
    return 1;
  }
  try
  {
    WorkerBST work(argv[1]);
    work.Menu();
  }
  catch (const std::exception& err)
  {
    std::cout << err.what();
    return 1;
  }
  return 0;
}
