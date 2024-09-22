#include <iostream>
#include <fstream>
#include "bintree.hpp"
int main()
{
  std::ifstream in("text.txt");
  if (!in.is_open())
  {
    std::cout << "Is not open\n";
    return 1;
  }
}
