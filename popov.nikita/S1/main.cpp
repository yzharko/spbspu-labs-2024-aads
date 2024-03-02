#include <iostream>
#include "list.hpp"

int main()
{
  using OutList = popov::List<std::pair<std::string,popov::List<int>>>;
  OutList OList;
  std::string input = "";
  while (std::cin.eof())
  {
    std::cin >> input;
    if (isdigit(input[0]))
    {
      OList.tail->data.second.pushBack(std::stoi(input));
    }
    else
    {
      OList.pushBack(std::pair<std::string,popov::List<int>> (input, popov::List<int>()));
    }
  }
  if (OList.head == nullptr)
  {
    std::cout << 0 << "\n";
  }
  while (OList.iter.node->next != nullptr)
  {
    std::cout << OList.iter.node->data.first << " ";
    OList.iter++;
  }
  std::cout << "\n";
  return 0;
}
