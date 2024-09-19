#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "AVL.hpp"
#include "Queue.hpp"

int main(int argc, char* argv[])
{
  try
  {
    zasulsky::AVL<int, std::string> tree;
    std::string arg;
    std::ifstream file;

    if (argc > 1)
    {
      arg = argv[1];
    }
    else
    {
      std::cerr << "not enough arguments passed\n";
      return 0;
    }

    if (argc > 2)
    {
      file.open(argv[2]);
    }

    if (file.is_open())
    {
      file.seekg(0, std::ios::end);
      if (file.tellg() == 0)
      {
        std::cout << "<EMPTY>";
        return 0;
      }
      else
      {
        file.seekg(0, std::ios::beg);
      }

      while (!file.eof())
      {
        std::string str;
        std::string strS;
        getline(file, str, ' ');
        getline(file, strS, ' ');
        tree.insert(make_pair(stoi(str), strS));
      }

      if (arg == "ascending")
      {
        tree.LNRTraversal();
      }
      else if (arg == "descending")
      {
        tree.RNLTraversal();
      }
      else if (arg == "breadth")
      {
        tree.breadthTraversal();
      }
      else
      {
        std::cerr << "unsupported bypass type\n";
      }
    }
    else
    {
      std::cerr << "file didn't open\n";
    }
  }

  catch (std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (...)
  {
    std::cerr << "exception\n";
    return 1;
  }
}

