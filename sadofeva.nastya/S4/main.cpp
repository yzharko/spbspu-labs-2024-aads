#include <fstream>
#include "AVLtree.hpp"
#include "Keystruct.hpp"


int main(int argc, char* argv[])
{
  if (argc != 3)
  {
     std::cerr << "Error. Invalid command\n";
     return 1;
  }
  std::string mode = argv[1];
  std::string filename = argv[2];

  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open file\n";
    return 1;
  }

  BinarySearchTree<int, std::string> tree;
  int key;
  std::string value;

  while (file >> key >> value)
  {
    tree.push(key, value);
  }
  if (tree.empty())
  {
    std::cout << "<EMPTY>\n";
    return 0;
  }
  sadofeva::KeyVal sum;

  try
    {
    if (mode == "ascending")
    {
      tree.traverse_lnr(sum);
    }
    else if (mode == "descending")
    {
      tree.traverse_rnl(sum);
    }
    else if (mode == "breadth")
    {
       tree.traverse_breadth(sum);
    }
    else
    {
      std::cerr << "Error: Invalid travels mode\n";
      return 1;
    }
    std::cout << sum.get_key_sum() << sum.get_val_sum() << "\n";
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
